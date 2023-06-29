/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_t_mini(t_minishell *mini)
{
	ft_printf("\n| pipe = %i\n", mini->pipe);
	ft_printf("| pipe_error = %i\n", mini->error_pipe);
	ft_printf("| redir_in = %i\n", mini->input_redirection);
	ft_printf("| redir_out = %i\n", mini->output_redirection);
	ft_printf("| redir_error = %i\n", mini->error_redir);
	ft_printf("| in_file = %s\n", mini->in_file);
	ft_printf("| out_file = %s\n\n", mini->out_file);
	ft_printf("input = %s\n", mini->cmd_table);
	return (0);
}

int	print_lst(t_lexer *lst)
{
	int i;

	i = 1;
	ft_printf("\n");
	while (lst != NULL)
	{
		printf("token %i = %s;\n", i, lst->content);
		lst = lst->next;
		i++;
	}
	return (0);
}

int	print_cmd_table(t_minishell *mini, int cmd)
{
	int i = 0;

	while (i < cmd)
	{
		printf("command %i = %s\n", i, mini->cmd_table[i]);
		i++;
	}
	return (0);
}
