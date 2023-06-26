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

int prompt(char **envp)
{
    char *input;

    input = readline("[Minishell] ");
    execute_command(input, envp);
	add_history(input);
	free(input);
	return (0);
}

int main(int argc, char **argv, char **envp)
{

    argv = NULL;
    argc = 0;
	(void)argv;
	(void)argc;
	print_opening();
    while(1)
    {
		prompt(envp);
    }
    return(0);
}

