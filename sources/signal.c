/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler_main(int s)
{
	if (s == SIGUSR1)
	{
		ft_putendl_fd("._-Farewell my friend-_'", 2);
		free_mini(mini_global);
		exit (EXIT_SUCCESS);
	}
	if (s == SIGINT) // ctrl c
	{
		ft_putendl_fd("", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void signal_main(t_minishell *mini, struct sigaction *sa_main)
{
	sa_main->sa_flags = SA_RESTART;

	mini_global = mini;
	sa_main->sa_handler = &signal_handler_main;
	sigemptyset(&sa_main->sa_mask);
	sigaction(SIGUSR1, sa_main, NULL);
	sigaction(SIGINT, sa_main, NULL);
}
