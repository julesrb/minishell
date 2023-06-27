/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* int	translate_token(t_lexer *lexer)
{
	t_lexer *curr;

	curr = lexer;
	while (curr != NULL)
	{
		if (curr->content[0] == '')
	}
} */

t_lexer	*build_command(t_minishell *t_mini, int cmd, t_lexer *lexer_pos)
{
	int arg;
	int a;
	t_lexer	*curr;

	arg = 0;
	a = 0;
	curr = lexer_pos;
	while (curr->content[0] != '|')
	{
		curr = curr->next;
		arg++;
	}
	while (a < cmd)
	{
		t_mini->cmd_table[cmd] = (char**)malloc(sizeof (char**));
		a++; 
	}
	return (curr);
}

int	parser(t_minishell *t_mini)
{
	int cmd;
	t_lexer	*curr;
	
	cmd = 0;
	curr = t_mini->lexer_table;
	t_mini->cmd_table = (char***)malloc(sizeof (char***) * t_mini->nb_cmd);

	// translate_var_token(curr); // translate the var
	// check_double_pipe;
	// check_redirection;
		// add the limiter option
	while (curr != NULL)
	{
		curr = build_command(t_mini, cmd, curr);
		curr = curr->next;
		cmd++;
	}
	
	return (1);
}