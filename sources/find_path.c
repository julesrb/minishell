/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:41:55 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/13 18:43:07 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_access_list_help(char *cmd_2, char **path_envp, int len, int i)
{
	char	**result;
	char	*temp;

	temp = NULL;
	result = (char **)malloc(sizeof(result) * ++len);
	if (!result)
		return (ft_free_pointer(cmd_2, NULL, NULL, path_envp));
	while (path_envp[i] != NULL)
	{
		temp = ft_strdup(path_envp[i]);
		result[i] = ft_strjoin(temp, cmd_2);
		if (!result[i])
			return (ft_free_pointer(cmd_2, NULL, result, path_envp));
		i++;
	}
	result[i] = NULL;
	ft_free_tab(path_envp);
	return (result);
}

char	**ft_access_list(char **cmd, t_minishell *mini)
{
	int		len;
	char	**result;
	char	**path_from_envp;
	char	*cmd_2;

	len = 0;
	cmd_2 = (char *)malloc(sizeof(cmd_2) * (ft_strlen(cmd[0]) + 2));
	if (!cmd_2)
		return (NULL);
	cmd_2[0] = '/';
	ft_strlcpy(cmd_2 + 1, cmd[0], ft_strlen(cmd[0]) + 1);
	path_from_envp = ft_split(getenv_mini("PATH", mini), ':');
	if (!path_from_envp)
		return (ft_free_pointer(cmd_2, NULL, NULL, NULL));
	while (path_from_envp[len] != NULL)
		len++;
	result = ft_access_list_help(cmd_2, path_from_envp, len, 0);
	if (!result)
		return (NULL);
	ft_free_pointer(cmd_2, NULL, NULL, NULL);
	return (result);
}

char	*ft_access_path(char **cmd, int i, t_minishell *mini)
{
	char	*result;
	char	**access_list;

	result = NULL;
	access_list = ft_access_list(cmd, mini);
	if (!access_list)
		return (NULL);
	while (access_list[i] != NULL)
	{
		if (access(access_list[i], F_OK | X_OK) == 0)
		{
			result = malloc(sizeof(result) * ft_strlen(access_list[i]));
			if (!result)
				return (ft_free_pointer(NULL, NULL, cmd, access_list));
			ft_strlcpy(result, access_list[i], ft_strlen(access_list[i]) + 1);
			break ;
		}
		i++;
	}
	ft_free_tab(access_list);
	return (result);
}
