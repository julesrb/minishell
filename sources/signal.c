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
		print_exit();
		free_mini(mini_global);
		if (mini_global->env_mini != NULL)
			deallocate_env(&mini_global->env_mini);
		exit (EXIT_SUCCESS);
	}
	if (s == SIGINT) // ctrl c
	{
		ft_putendl_fd("", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//ft_printf("sign pid = %d", getpid());
	}
}

void signal_main(t_minishell *mini)
{
	mini_global = mini;

	struct sigaction	sa_main;

	sa_main.sa_handler = &signal_handler_main;
	sigemptyset(&sa_main.sa_mask);
	sa_main.sa_flags = SA_RESTART;

	sigaction(SIGUSR1, &sa_main, NULL);
	sigaction(SIGINT, &sa_main, NULL);

	struct sigaction	sa_quit;

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;

	sigaction(SIGQUIT, &sa_quit, NULL);
}

void signal_handler_cmd(int s)
{
	if (s == SIGUSR1)
	{
		print_exit();
		free_mini(mini_global);
		if (mini_global->env_mini != NULL)
			deallocate_env(&mini_global->env_mini);
		exit (EXIT_SUCCESS);
	}
	if (s == SIGINT) // ctrl c
	{
		ft_printf("******");

	}
}

void signal_cmd(t_minishell *mini)
{

	struct sigaction	sa_cmd;

	sa_cmd.sa_handler = &signal_handler_cmd;
	sigemptyset(&sa_cmd.sa_mask);
	sa_cmd.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa_cmd, NULL);
	(void)mini;

/* 	struct sigaction	sa_quit;

	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;

	sigaction(SIGQUIT, &sa_quit, NULL); */
}
