/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:21:29 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/11 19:24:43 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	max_length(const char *str1, const char *str2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", max_length("pwd", cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", max_length("env", cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", max_length("cd", cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", max_length("export", cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", max_length("unset", cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", max_length("echo", cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", max_length("exit", cmd)) == 0)
		return (1);
	return (0);
}

int	is_env_function(char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", max_length("cd", cmd[0])) == 0)
		return (1);
	else if ((ft_strncmp(cmd[0], "export", max_length("export", cmd[0])) == 0) && ft_tablen(cmd) > 1)
		return (1);
	else if (ft_strncmp(cmd[0], "unset", max_length("unset", cmd[0])) == 0)
		return (1);
	return (0);
}
