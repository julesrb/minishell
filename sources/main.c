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
    int     pipe_nb;
    int i = 0;

    argv = NULL;
    argc = 0;
	print_opening();
    while(1)
    {
        input = readline("[Minishell] ");
        pipe_nb = 0;
        while (i <= pipe_nb)
        {
            execute_command(input, envp);
            i++;
        }
        add_history(input);
    }
    free(input);
    return(0);
} */

int main(int argc, char **argv, char **envp)
{
/*     int i = 0; */
    char input1[] = "cat file1";
    char input2[] = "grep a";

    argv = NULL;
    argc = 0;
/* 	print_opening(); */
    executor(input1, envp);
    executor(input2, envp);
/*         while (i <= pipe_nb)
        {
            execute_command(input, envp);
            i++;
        } */
/*         add_history(input); */
/*     free(input); */
    return(0);
}