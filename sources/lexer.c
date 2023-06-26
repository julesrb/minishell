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

/* int	yield_pipe(char *token, t_minishell *t_mini)
{
	t_mini->pipe += 1;
	return (0);
} */

int	yield_redirection(char *token, t_minishell *t_mini)
{
	// think about edge case like <> or ><

	if (token[0] == '<')
	{
		t_mini->input_redirection = 1;
		if (token[1] == '<')
		{
			t_mini->input_redirection = 2;
			return (2);
		}
		return (1);
	}
	else if (token[0] == '>')
	{
		t_mini->output_redirection = 1;
		if (token[1] == '>')
		{
			t_mini->output_redirection = 2;
			return (2);
		}
		return (1);
	}
	return (0);
}

int	lexer(t_minishell *t_mini)
{
	 // deal with " "
	 // deal with ''
	 // deal with |
	 // deal with < << >> >
	 // deal with strings
		 // deal with command
	 // deal with $
	char *input;
	int i;

	i = 0;
	input = t_mini->input;
	while (input[i] != 0)
	{
		if (input[i] == '<' || input[i] == '>')
			i += yield_redirection(&input[i], t_mini);
	/* 	else if (input[i] == '|')
			i += yield_pipe(&input[i], t_mini);
		else if (input[i] == '$')
			i += yield_env_var(&input[i], t_mini);
		else if (input[i] == 39)
			i += yield_single_quote(&input[i], t_mini);
		else if (input[i] == 34)
			i += yield_double_quote(&input[i], t_mini);
		else if (ft_isalpha(input[i]) == 1)
			i += yield_string(&input[i], t_mini); */
		else
			i++;
	}
	free(input);
	return (0);
}