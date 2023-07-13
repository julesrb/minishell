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

void	signal_handler_main(int s)
{
	if (s == SIGUSR1)
	{
		print_exit();
		free_mini(mini_global);
		if (mini_global->env_mini != NULL)
			deallocate_env(&mini_global->env_mini);
		exit (EXIT_SUCCESS);
	}
	if (s == SIGQUIT)
	{
		if (mini_global->execute == 1)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	if (s == SIGINT)
	{
		ft_putendl_fd("", 2);
		if (mini_global->execute == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	signal_main(t_minishell *mini)
{
	struct sigaction	sa_main;
	struct sigaction	sa_quit;

	mini_global = mini;
	sa_main.sa_handler = &signal_handler_main;
	sigemptyset(&sa_main.sa_mask);
	sa_main.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa_main, NULL);
	sigaction(SIGINT, &sa_main, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	signal_handler_child(int s)
{
	if (s == SIGQUIT)
	{
		if (mini_global->execute == 1)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
}

void	signal_command(t_minishell *mini)
{
	struct sigaction	sa_quit_cmd;

	mini->execute = 1;
	sa_quit_cmd.sa_handler = &signal_handler_child;
	sigemptyset(&sa_quit_cmd.sa_mask);
	sa_quit_cmd.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit_cmd, NULL);
}
