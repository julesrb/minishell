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

int	token_yield_word(char *token, t_minishell *mini)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	while (token[len] != ' ' && token[len] != 0 && token[len] != '|'
		&& token[len] != 34 && token[len] != 39)
		len++;
	if (token[len] == 34 || token[len] == 39)
	{
		len++;
		while (token[len] != 34 && token[len] != 39 && token[len] != 0)
			len++;
		if (token[len] != 0)
			len++;
	}
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < len)
		str[i] = token[i];
	str[i] = '\0';
	add_to_list(&mini->lexer_table, str);
	return (i);
}

int	token_yield_quote(char *token, t_minishell *mini)
{
	int		i;
	int		len;
	char	*str;

	i = 1;
	while (token[i] != token[0] && token[i] != 0)
		i++;
	len = i;
	if (token[i] == token[0])
		len++;
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		str[i] = token[i];
		i++;
	}
	str[i] = '\0';
	add_to_list(&mini->lexer_table, str);
	return (i + 1);
}

int	token_yield_var(char *token, t_minishell *mini)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	while (token[len] != ' ' && token[len] != 0)
		len++;
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		str[i] = token[i];
		i++;
	}
	str[i] = '\0';
	add_to_list(&mini->lexer_table, str);
	return (EXIT_SUCCESS);
}

int	token_yield_pipe(char *token, t_minishell *mini)
{
	char	*str;

	mini->pipe += 1;
	str = malloc(sizeof (char) * (1 + 1));
	if (!str)
		return (EXIT_FAILURE);
	str[0] = token[0];
	str[1] = 0;
	add_to_list(&mini->lexer_table, str);
	return (EXIT_SUCCESS);
}

int	token_yield_redir(char *redir, t_minishell *mini)
{
	char	*str;

	if (redir[0] != redir[1])
	{
		str = malloc(sizeof (char) * (1 + 1));
		if (!str)
			return (EXIT_FAILURE);
		str[0] = redir[0];
		str[1] = 0;
		add_to_list(&mini->lexer_table, str);
		return (1);
	}
	if (redir[0] == redir[1])
	{
		str = malloc(sizeof (char) * (2 + 1));
		if (!str)
			return (EXIT_FAILURE);
		str[0] = redir[0];
		str[1] = redir[1];
		str[2] = 0;
		add_to_list(&mini->lexer_table, str);
		return (2);
	}
	return (EXIT_FAILURE);
}
