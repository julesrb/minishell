/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_last_token_is_pipe(t_llist *curr)
{
	while (curr->next != NULL)
		curr = curr->next;
	if (curr->content[0] == '|')
		return (1);
	return (0);
}

int	lexer_error_pipe_check(t_minishell *mini)
{
	t_llist	*curr;

	curr = mini->lexer_table;
	if (!curr)
		return (0);
	if (curr->content[0] == '|')
		mini->error_pipe = 1;
	if (lexer_last_token_is_pipe(curr) == 1)
		mini->error_pipe = 1;
	while (curr->next != NULL)
	{
		if (curr->content[0] == '|' && curr->next->content[0] == '|')
			mini->error_pipe = 1;
		curr = curr->next;
	}
	return (1);
}

int	lexer_iswordstart(char c)
{
	if (c == '-'	|| c == '.' || c == '=' || c == '/'
		|| c == '~' || c == '(')
		return (1);
	else
		return (0);
}

int	lexer(t_minishell *mini)
{
	int		i;

	i = 0;
	if (mini->error == 1)
		return (0);
	while (mini->input[i] != 0)
	{
		if (mini->input[i] == '<' || mini->input[i] == '>')
			PROCESS_TOKEN(token_yield_redir, mini->input, i, mini);
		else if (ft_isalnum(mini->input[i]) != 0 || lexer_iswordstart(mini->input[i]) == 1)
			PROCESS_TOKEN(token_yield_word, mini->input, i, mini);
		else if (mini->input[i] == 39 || mini->input[i] == 34)
			PROCESS_TOKEN(token_yield_quote, mini->input, i, mini);
		else if (mini->input[i] == '$')
			PROCESS_TOKEN(token_yield_var, mini->input, i, mini);
		else if (mini->input[i] == '|' )
			PROCESS_TOKEN(token_yield_pipe, mini->input, i, mini);
		else
			i++;
	}
	mini->nb_cmd = mini->pipe + 1;
	lexer_error_pipe_check(mini);
	if (!mini->lexer_table)
		mini->error = 1;
	return (1);
}
