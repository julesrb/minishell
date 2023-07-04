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

int	init_t_mini(t_minishell *mini, char **envp)
{
	mini->envp = envp;
	mini->input = NULL;
	mini->lexer_table = NULL;
	mini->cmd_table = NULL;
	mini->limiter = NULL;
	mini->in_file = NULL;
	mini->out_file = NULL;
	mini->pipe = 0;
	mini->input_redirection = 0;
	mini->output_redirection = 0;
	mini->nb_cmd = 0;
	mini->error_redir = 0;
	mini->error_pipe = 0;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell mini;

	mini.exit_status = 0;
	arg_check(argc, argv);
	if (env_mini(&mini, envp) == EXIT_FAILURE)
		printf("Error initializing the minishell environment\n");
	print_opening();
	while(1)
	{
		init_t_mini(&mini, envp);
		prompt(&mini);
		lexer(&mini);
 			//print_lst(mini.lexer_table); 
		parser(&mini);
 			print_t_mini(&mini);
			print_cmd_table(&mini, mini.nb_cmd);
		if ((mini.error_pipe == 0 && mini.error_redir == 0) || mini.nb_cmd > 0)
				mini.exit_status = executor(&mini, envp);
		else
			ft_printf("Parsing ERROR\n");
		free_mini(&mini);
	}
	return(0);
}
