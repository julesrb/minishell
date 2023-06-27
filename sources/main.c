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

/* int main(int argc, char **argv, char **envp)
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
        input = readline("[Minishell] ");
        execute_command(input, envp);
        add_history(input);
    }
    return(0);
} */

int main(int argc, char **argv, char **envp)
{
    t_minishell     mini;

    mini.cmd_table = (char **)malloc(sizeof(mini.cmd_table) * 2);
    mini.cmd_table[0] = ft_strdup("<<EOF");
    mini.cmd_table[1] = ft_strdup("sort");  
    mini.cmd_table[2] = ft_strdup("grep b");
    mini.cmd_table[3] = ft_strdup("file2");
    mini.pipe = 1;
    mini.input_redirection = 2;
    mini.output_redirection = 1;
    mini.nb_cmd = 1;
    argv = NULL;
    argc = argc + 3;
	print_opening();
    executor(mini, envp);
    return(0);
}