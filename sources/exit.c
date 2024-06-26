/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_builtin(char **cmd, t_minishell *mini)
{
	int	i;

	i = 0;
	(void)mini;
	while (cmd[i] != NULL)
		i++;
	if (i > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": too many arguments", 2);
		return (0);
	}
	banner_print_exit();
	free_mini(g_mini);
	if (g_mini->env_mini != NULL)
		deallocate_env(&g_mini->env_mini);
	exit (EXIT_SUCCESS);
	return (1);
}
