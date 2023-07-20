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

int	lexer_iswordstart(char c)
{
	if (c == '-' || c == '.' || c == '=' || c == '/'
		|| c == '~' || c == '(' || c == '+')
		return (1);
	else
		return (0);
}

int	tokfun(int *i, int *a, int (*fun)(char *, t_minishell *), t_minishell *mini)
{
	*a = fun(&(mini->input[*i]), mini);
	if (*a == -1)
		return (0);
	*i = *i + *a;
	return (1);
}

int	lexer(t_minishell *mini, int i, int a, int b)
{
	if (mini->error == 1)
		return (1);
	while (mini->input[i] != 0)
	{
		if (mini->input[i] == '<' || mini->input[i] == '>')
			b = tokfun(&i, &a, token_yield_redir, mini);
		else if (ft_isalnum(mini->input[i]) != 0
			|| lexer_iswordstart(mini->input[i]) == 1)
			b = tokfun(&i, &a, token_yield_word, mini);
		else if (mini->input[i] == 39 || mini->input[i] == 34)
			b = tokfun(&i, &a, token_yield_quote, mini);
		else if (mini->input[i] == '$')
			b = tokfun(&i, &a, token_yield_var, mini);
		else if (mini->input[i] == '|')
			b = tokfun(&i, &a, token_yield_pipe, mini);
		else
			i++;
		if (b == 0)
			return (0);
	}
	if (!mini->lexer_table)
		mini->error = 1;
	mini->nb_cmd = mini->pipe + 1;
	return (1);
}
