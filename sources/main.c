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

int	yield_redirection(char *token)
{

	return (1);
}

char *lexer(char *input)
{
	 // deal with " "
	 // deal with ''
	 // deal with |
	 // deal with < << >> >
	 // deal with strings
		 // deal with command
	 // deal with $

	int i;

	i = 0;
	while (input[i] != 0)
	{
		if (input[i] == "<" || input[i] == ">")
			i += yield_redirection(input[i]);
		else if (input[i] == "|")
			i += yield_pipe(input[i]);
		else if (ft_isalpha(input[i]) == 1)
			i += yield_string(input[i]);
		else if (input[i] == "$")
			i += yield_env_var(input[i]);
		else if (input[i] == 39)
			i += yield_single_quote(input[i]);
		else if (input[i] == 34)
			i += yield_double_quote(input[i]);
		else
			i++;
	}
	free(input);
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	char *input;

    argv = NULL;
    argc = 0;
	(void)argv;
	(void)argc;
	(void)input;
	print_opening();
    while(1)  
    {
		input = prompt(envp);
		lexer(input);
	
		//execute_command(input, envp);
    }
    return(0);
}

