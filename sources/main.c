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

t_minishell	*g_mini;

int	ft_failure(char *str, int exit_n, int fr_mini, int fr_env)
{
	g_mini->error = 1;
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	if (fr_env == 1)
		deallocate_env(&g_mini->env_mini);
	if (fr_mini == 1)
		free_mini(g_mini);
	if (exit_n != 0)
		exit(exit_n);
	return (1);
}

void	init_t_mini(t_minishell *mini)
{
	mini->input = NULL;
	mini->cmd_table = NULL;
	mini->redir_end = NULL;
	mini->redir_start = NULL;
	mini->lexer_table = NULL;
	mini->pipe = 0;
	mini->error = 0;
	mini->nb_cmd = 0;
	mini->execute = 0;
	mini->error_malloc = 0;
	mini->error_pipe = 0;
	mini->error_redir = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	g_mini = &mini;
	mini.exit_status = 0;
	arg_check(argc, argv);
	env_mini(&mini, envp);
	banner_print_opening();
	while (1)
	{
		signal_main();
		init_t_mini(&mini);
		if (!prompt(&mini))
			ft_failure("readline failed", 0, 1, 0);
		if (!lexer(&mini))
			ft_failure("lexer alloc failed", 0, 1, 0);
 						/* print_lst(mini.lexer_table); */
		if (mini.error == 0)
			if (!parser(&mini))
				ft_failure("parser alloc failed", 0, 1, 0);
 						/* print_t_mini(&mini); */
						/* print_cmd_table(&mini, mini.nb_cmd); */
		if (mini.error == 0)
			executor(&mini);
		free_mini(&mini);
	}
	return (EXIT_SUCCESS);
}
