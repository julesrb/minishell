/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:44:04 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/13 18:50:35 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenv_mini(char *env_mini, t_minishell *mini)
{
	t_list	*curr;

	curr = mini->env_mini;
	while (curr != NULL)
	{
		if (ft_strncmp(env_mini, curr->content, ft_strlen(env_mini)) == 0)
			return (curr->content + ft_strlen(env_mini) + 1);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_count_trim(char *cmd)
{
	int	count_trim;
	int	i;

	i = 0;
	count_trim = 0;
	if (!cmd)
		return (count_trim);
	while (cmd[i] && (!ft_isalnum(cmd[i]) && !ft_isalnum(cmd[i + 1])
			&& !ft_isalnum(cmd[i + 2])))
	{
		if (cmd[i] == '.' && cmd[i + 1] == '.' && cmd[i + 2] == '/')
			count_trim++;
		i = i + 3;
	}
	return (count_trim);
}

char	*origine_path(int count_trim, t_minishell *mini)
{
	char	*current_path;
	char	*or_path;
	int		i;
	int		j;
	int		nb;

	nb = 0;
	i = 0;
	j = 0;
	current_path = ft_strdup(getenv_mini("PWD", mini));
	while (current_path[i] != '\0')
	{
		if (current_path[i] == '/')
			nb++;
		i++;
	}
	nb++;
	i = 0;
	while (current_path[i] != '\0')
	{
		if (current_path[i] == '/')
			j++;
		if (j == (nb - count_trim))
			break ;
		i++;
	}
	or_path = (char *)malloc(sizeof(or_path) * (i + 1));
	ft_strlcpy(or_path, current_path, i + 1);
	free(current_path);
	return (or_path);
}

char	*ft_relative_path(char *cmd, t_minishell *mini)
{
	char	*relative_path;
	char	*path_trim;
	char	*env_path;
	char	*path_root;
	int		count_trim;

	relative_path = NULL;
	path_trim = NULL;
	path_root = NULL;
	count_trim = 0;
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		path_trim = ft_strtrim(cmd, "./");
		env_path = ft_strdup(getenv_mini("PWD", mini));
		relative_path = ft_strjoin(env_path, (char *)"/");
		relative_path = ft_strjoin(relative_path, path_trim);
	}
	else if (ft_strncmp(cmd, "../", 3) == 0)
	{
		path_trim = ft_strtrim(cmd, "./");
		count_trim = ft_count_trim(cmd);
		env_path = origine_path(count_trim, mini);
		path_root = ft_strjoin(env_path, (char *)"/");
		relative_path = ft_strjoin(path_root, path_trim);
	}
	free(path_trim);
	return (relative_path);
}

int	is_relative_path(char *path)
{
	if (ft_strlen(path) >= 2 && (ft_strncmp(path, "./", 2) == 0
			|| ft_strncmp(path, "../", 3) == 0))
		return (EXIT_SUCCESS);
	else if (ft_strlen(path) == 1 && path[0] == '.')
		return (EXIT_SUCCESS);
	else if (ft_strlen(path) == 2 && ft_strncmp(path, "..", 2) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	is_absolute_path(char *path)
{
	if (ft_strlen(path) >= 1 && path[0] == '/')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

char	*find_executable(char **cmd, t_minishell *mini)
{
	char	*result;

	result = NULL;
	if (is_absolute_path(cmd[0]) == EXIT_SUCCESS)
		result = ft_strdup(cmd[0]);
	else if (is_relative_path(cmd[0]) == EXIT_SUCCESS)
		result = ft_relative_path(cmd[0], mini);
	else
		result = ft_access_path(cmd, 0, mini);
	return (result);
}
