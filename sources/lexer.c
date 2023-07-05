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

int	yield_word(char *token, t_minishell *mini)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	while (token[len] != ' ' && token[len] != 0 && token[len] != '|')
	{
		if (token[len] == 34 || token[len] == 39)
			while ((token[len] != 34 && token[len] != 39) || token[len + 1] != 0)
				len++;
		len++;
	}
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = token[i];
		i++;
	}
	str[i] = '\0';
	add_to_list(&mini->lexer_table, str);
	return (i);
}

int	yield_quote(char *token, t_minishell *mini)
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
		return (0);
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

int	yield_var(char *token, t_minishell *mini)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	while (token[len] != ' ' && token[len] != 0)
		len++;
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = token[i];
		i++;
	}
	str[i] = '\0';
	add_to_list(&mini->lexer_table, str);
	return (i);
}

int	yield_pipe(char *token, t_minishell *mini)
{
	char	*str;

	mini->pipe += 1;
	str = malloc(sizeof (char) * (1 + 1));
	str[0] = token[0];
	str[1] = 0;
	add_to_list(&mini->lexer_table, str);
	return (1);
}

int	yield_redirection(char *redir, t_minishell *mini)
{
	char	*str;

	if (redir[0] != redir[1])
	{
		str = malloc(sizeof (char) * (1 + 1));
		str[0] = redir[0];
		str[1] = 0;
		add_to_list(&mini->lexer_table, str);
		return (1);
	}
	if (redir[0] == redir[1])
	{
		str = malloc(sizeof (char) * (2 + 1));
		str[0] = redir[0];
		str[1] = redir[1];
		str[2] = 0;
		add_to_list(&mini->lexer_table, str);
		return (2);
	}
	return (0);
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
			i += yield_redirection(&input[i], mini);
		else if (ft_isalpha(input[i]) == 1 || input[i] == '-' || input[i] == '.' || input[i] == '=' || input[i] == '/')
			i += yield_word(&input[i], mini);
		else if (input[i] == 39 || input[i] == 34)
			i += yield_quote(&input[i], mini);
		else if (input[i] == '$')
			i += yield_var(&input[i], mini);
		else if (input[i] == '|' )
			i += yield_pipe(&input[i], mini);
		else
			i++;
	}
	mini->nb_cmd = mini->pipe + 1;
	return (0);
}
