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

int	init_t_mini(t_minishell *t_mini)
{
	t_mini->input = NULL;
	t_mini->cmd_table = NULL;
	t_mini->pipe = 0;
	t_mini->input_redirection = 0;
	t_mini->output_redirection = 0;
	t_mini->nb_cmd = 0;
	return (0);
}


int main(int argc, char **argv, char **envp)
{
	t_minishell t_mini;

	(void)argv;
	(void)argc;
	print_opening();
    while(1)  
    {
		init_t_mini(&t_mini);
		prompt(envp, &t_mini);
		lexer(&t_mini);
	
		//execute_command(input, envp);
    }
    return(0);
}

