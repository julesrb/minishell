/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*mini_global;

int	init_t_mini(t_minishell *mini)
{
	mini->input = NULL;
	mini->cmd_table = NULL;
	mini->lexer_table = NULL;
	mini->redir_in = NULL;
	mini->redir_out = NULL;
	mini->pipe = 0;
	mini->nb_cmd = 0;
	mini->error_redir = 0;
	mini->error_pipe = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	//struct sigaction	sa_main;
	t_minishell			mini;

	//signal_main(&mini, &sa_main);
	//signal(SIGQUIT, SIG_IGN);
	mini.exit_status = 0;
	arg_check(argc, argv);
	if (env_mini(&mini, envp) == EXIT_FAILURE)
		ft_putendl_fd("Error initializing the minishell environment", 2);
	print_opening ();
	while (1)
	{
		init_t_mini(&mini);
		prompt(&mini);
		lexer(&mini);
/*  			print_lst(mini.lexer_table);  */
		parser(&mini);
/*  			print_t_mini(&mini);
			print_cmd_table(&mini, mini.nb_cmd); */
 		if ((mini.error_pipe == 0 && mini.error_redir == 0)
			&& (mini.nb_cmd > 0 || mini.redir_in || mini.redir_out))
			mini.exit_status = executor(&mini);
		else if (mini.nb_cmd != 0)
			ft_putendl_fd("minishell: parsing error", 2);
		free_mini(&mini);
	}
	return (EXIT_SUCCESS);
}
