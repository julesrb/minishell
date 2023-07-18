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

char	*origine_path(int count_trim, t_minishell *mini, int j, int nb)
{
	char	*current_path;
	char	*or_path;
	int		i;

	i = 0;
	current_path = ft_strdup(getenv_mini("PWD", mini));
	while (current_path[i] != '\0')
	{
		if (current_path[i++] == '/')
			nb++;
	}
	nb++;
	i = 0;
	while (current_path[i] != '\0')
	{
		if (current_path[i++] == '/')
			j++;
		if (j == (nb - count_trim))
			break ;
	}
	or_path = (char *)malloc(sizeof(or_path) * (i + 1));
	ft_strlcpy(or_path, current_path, i + 1);
	free(current_path);
	return (or_path);
}

char	*ft_relative_path(char *cmd, t_minishell *mini, char *temp, char *temp2)
{
	char	*relative_path;
	char	*env_path;
	int		count_trim;

	relative_path = NULL;
	count_trim = 0;
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		temp = ft_strtrim(cmd, "./");
		env_path = ft_strdup(getenv_mini("PWD", mini));
		relative_path = ft_strjoin(env_path, (char *)"/");
		relative_path = ft_strjoin(relative_path, temp);
	}
	else if (ft_strncmp(cmd, "../", 3) == 0)
	{
		temp = ft_strtrim(cmd, "./");
		count_trim = ft_count_trim(cmd);
		env_path = origine_path(count_trim, mini, 0, 0);
		temp2 = ft_strjoin(env_path, (char *)"/");
		relative_path = ft_strjoin(temp2, temp);
	}
	free(temp);
	return (relative_path);
}
