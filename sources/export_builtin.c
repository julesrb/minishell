/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:59:32 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/13 19:12:25 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*adjust_help2(t_minishell *mini, char *start, char *end)
{
	char	*rslt;
	char	*temp_trim;
	char	*temp;

	temp = NULL;
	rslt = NULL;
	temp_trim = NULL;
	temp_trim = ft_strtrim(end, (const char *)"\"");
	if (ft_strrchr(temp_trim, '$') != NULL)
	{
		temp = translate_var(mini, temp_trim);
		rslt = ft_strjoin(start, temp);
		free(temp);
	}
	else
	{
		rslt = ft_strjoin(start, temp_trim);
		free(temp_trim);
	}
	return (rslt);
}

char	*adjust_help1(t_minishell *mini, char *var_env, char *start, char *end)
{
	char	*rslt;
	char	*temp_trim;

	rslt = NULL;
	temp_trim = NULL;
	if (ft_strchr(var_env, '\"') != NULL)
		rslt = adjust_help2(mini, start, end);
	else if (ft_strchr(var_env, '\'') != NULL)
	{
		temp_trim = ft_strtrim(end, (const char *)"\'");
		rslt = ft_strjoin(start, temp_trim);
		free(temp_trim);
	}
	else
	{
		free(start);
		rslt = ft_strdup(var_env);
	}
	free(end);
	return (rslt);
}

char	*adjust_var_env(t_minishell *mini, char *var_env, int count)
{
	char	*rslt;
	char	*temp_end;
	char	*temp_start;

	rslt = NULL;
	while (var_env[count] && (var_env[count] != '='))
		count++;
	temp_start = (char *)malloc(sizeof(temp_start) * (count));
	ft_strlcpy(temp_start, var_env, count + 2);
	temp_end = ft_strdup(var_env + count + 1);
	rslt = adjust_help1(mini, var_env, temp_start, temp_end);
	return (rslt);
}

int	export_with_arg(t_minishell *mini, char **cmd, int i, char *new_var)
{
	t_list	*new;

	while (cmd[i] && (check_arg_export(cmd[i]) == EXIT_SUCCESS))
	{
		if (check_update_var(cmd[i], mini->env_mini) == EXIT_SUCCESS)
		{
			new_var = adjust_var_env(mini, cmd[i], 0);
			if (list_env_update(mini, new_var) == EXIT_FAILURE)
				return (ft_free_fail(new_var, NULL, NULL, NULL));
		}
		else
		{
			new_var = adjust_var_env(mini, cmd[i], 0);
			new = ft_lstnew((void *)ft_strdup(new_var));
			if (!new)
				return (ft_free_fail(new_var, NULL, NULL, NULL));
			ft_lstadd_back(&mini->env_mini, new);
		}
		i++;
		free(new_var);
		if (!cmd[i])
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	export_builtin(char **cmd, t_minishell *mini)
{
	t_list	*curr;
	int		i;

	curr = mini->env_mini;
	i = 0;
	while (cmd[i] != NULL)
		i++;
	if (i == 1)
	{
		while (curr)
		{
			printf("declare -x %s\n", (char *)(curr->content));
			curr = curr->next;
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		if (export_with_arg(mini, cmd, 1, NULL) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		ft_putendl_fd("memory allocation failes", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
