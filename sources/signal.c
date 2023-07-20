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

void	signal_here_handler(int s)
{
	if (s == SIGINT)
	{
			ft_putendl_fd("i made it here", 2);
			ft_printf("i made it here");

	}
}

void	signal_here(void)
{
	struct sigaction	sa_here;

	sa_here.sa_handler = &signal_here_handler;
	sigemptyset(&sa_here.sa_mask);
	sa_here.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_here, NULL);
}

void	signal_command_handler(int s)
{
	if (s == SIGQUIT)
	{
		if (g_mini->execute == 1)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
}

void	signal_command(t_minishell *mini)
{
	struct sigaction	sa_quit_cmd;

	mini->execute = 1;
	sa_quit_cmd.sa_handler = &signal_command_handler;
	sigemptyset(&sa_quit_cmd.sa_mask);
	sa_quit_cmd.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit_cmd, NULL);
}

void	signal_main_handler(int s)
{
	if (s == SIGUSR1)
	{
		banner_print_exit();
		free_mini(g_mini);
		if (g_mini->env_mini != NULL)
			deallocate_env(&g_mini->env_mini);
		exit (EXIT_SUCCESS);
	}
	if (s == SIGQUIT)
	{
		if (g_mini->execute == 1)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	if (s == SIGINT)
	{
		if (g_mini->here_doc_pid != 0)
		{
			ft_printf("i'm in here\n");
			return;
		}
		ft_putendl_fd("", 2);
		//ft_printf("i'm in between\n");
		ft_printf("pid main = %i\n", g_mini->main_pid);
		ft_printf("pid child = %i\n", g_mini->child_pid);
		ft_printf("pid here = %i\n", g_mini->here_doc_pid);
		if (g_mini->execute == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	signal_main(void)
{
	struct sigaction	sa_main;
	struct sigaction	sa_quit;

	sa_main.sa_handler = &signal_main_handler;
	sigemptyset(&sa_main.sa_mask);
	sa_main.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa_main, NULL);
	sigaction(SIGINT, &sa_main, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
