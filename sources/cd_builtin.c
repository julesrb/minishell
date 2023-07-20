/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:10:37 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/12 17:31:56 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_path_to_absolute(char **cmd, t_minishell *mini)
{
	char	*result;
	int		tab_len;

	tab_len = ft_tablen(cmd);
	if (tab_len == 1)
		return (ft_relative_path_cd("~", mini));
	if (is_absolute_path(cmd[1]) == EXIT_SUCCESS)
	{
		if ((cmd[1][ft_strlen(cmd[1]) - 1] == '/') && (ft_strlen(cmd[1]) > 1))
		{
			result = ft_strdup(cmd[1]);
			ft_bzero((void *)(result + ft_strlen(cmd[1]) - 1), 1);
		}
		else
			result = ft_strdup(cmd[1]);
		return (result);
	}
	else if ((is_relative_path(cmd[1]) == 0) || ((ft_strlen(cmd[1]) == 1)
			&& (cmd[1][0] == '-')) || ((ft_strlen(cmd[1]) == 1)
			&& (cmd[1][0] == '~')))
		return (ft_relative_path_cd(cmd[1], mini));
	else
		return (ft_relative_path_cd(cmd[1], mini));
	return (NULL);
}

int	update_env_mini(t_minishell *mini, char *up_var, char *new_value)
{
	t_list	*curr;
	char	*new_var_env;
	char	*temp1;
	char	*temp2;

	new_var_env = NULL;
	temp1 = NULL;
	temp2 = NULL;
	curr = mini->env_mini;
	while (curr != NULL)
	{
		if (ft_strncmp(up_var, (char *)(curr->content), ft_strlen(up_var)) == 0)
		{
			free(curr->content);
			temp1 = ft_strdup(up_var);
			temp2 = ft_strjoin(temp1, (char *)"=");
			temp1 = ft_strdup(new_value);
			new_var_env = ft_strjoin(temp2, temp1);
			free(temp1);
			curr->content = (void *)new_var_env;
			return (EXIT_SUCCESS);
		}
		curr = curr->next;
	}
	return (EXIT_FAILURE);
}

int	update_env_cd(t_minishell *mini, char **cd)
{
	char	*oldpwd;
	char	*pwd;

	pwd = convert_path_to_absolute(cd, mini);
	if (!pwd)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (EXIT_FAILURE);
	}
	oldpwd = ft_strdup(getenv_mini("PWD", mini));
	if (!oldpwd)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (EXIT_FAILURE);
	}
	if (update_env_mini(mini, "OLDPWD", oldpwd) == EXIT_FAILURE)
		return (ft_free_fail(pwd, oldpwd, NULL, NULL));
	if (update_env_mini(mini, "PWD", pwd) == EXIT_FAILURE)
		return (ft_free_fail(pwd, oldpwd, NULL, NULL));
	return (ft_free_success(pwd, oldpwd, NULL, NULL));
}

int	chdir_error(char **cmd, char *cmd_replace)
{
	if (chdir(cmd_replace) == -1)
	{
		free(cmd_replace);
		ft_putstr_fd("cd: ", 2);
		perror(cmd[1]);
		return (1);
	}
	return (0);
}

int	cd_builtin(char **cmd, t_minishell *mini, char *cmd_replace)
{
	int		tab_len;

	tab_len = ft_tablen(cmd);
	if (tab_len > 2)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(cmd[1], 2);
	}
	if ((tab_len == 1) || ((cmd[1][0] == '~') && (ft_strlen(cmd[1]) == 1)))
		cmd_replace = ft_strdup(getenv_mini("HOME", mini));
	else if ((ft_strlen(cmd[1]) == 1) && (cmd[1][0] == '-'))
		cmd_replace = ft_strdup(getenv_mini("OLDPWD", mini));
	else
		cmd_replace = ft_strdup(cmd[1]);
	if (!cmd_replace)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (EXIT_FAILURE);
	}
	if (chdir_error(cmd, cmd_replace))
		return (EXIT_FAILURE);
	free(cmd_replace);
	if (update_env_cd(mini, cmd) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
