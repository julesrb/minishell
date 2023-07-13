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
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

int	lexer(t_minishell *mini)
{
	char	*input;
	int		i;

	i = 0;
	input = mini->input;
	while (input[i] != 0)
	{
		if (input[i] == '<' || input[i] == '>')
			i += token_yield_redir(&input[i], mini);
		else if (ft_isalnum(input[i]) != 0 || input[i] == '-' || input[i] == '.'
			|| input[i] == '=' || input[i] == '/'
			|| input[i] == '~' || input[i] == '(')
			i += token_yield_word(&input[i], mini);
		else if (input[i] == 39 || input[i] == 34)
			i += token_yield_quote(&input[i], mini);
		else if (input[i] == '$')
			i += token_yield_var(&input[i], mini);
		else if (input[i] == '|' )
			i += token_yield_pipe(&input[i], mini);
		else
			i++;
	}
	mini->nb_cmd = mini->pipe + 1;
	lexer_error_pipe_check(mini);
	return (EXIT_SUCCESS);
}
