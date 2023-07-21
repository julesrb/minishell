/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(char **cmd_split)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	if (cmd_split[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(cmd_split[i], "-n", 2) == EXIT_SUCCESS)
	{
		n = 0;
		i++;
	}
	while (cmd_split[i] != NULL)
	{
		ft_putstr_fd(cmd_split[i], 1);
		if (cmd_split[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == 1)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
