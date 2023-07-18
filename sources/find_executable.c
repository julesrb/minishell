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
		result = ft_relative_path(cmd[0], mini, NULL, NULL);
	else
		result = ft_access_path(cmd, 0, mini);
	return (result);
}
