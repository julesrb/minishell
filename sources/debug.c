/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_lst_redir(t_redir *lst)
{
	int i;

	i = 1;
	while (lst != NULL)
	{
		ft_printf("%i - %s; ", lst->type, lst->file);
		lst = lst->next;
		i++;
	}
	return (0);
}

int	print_t_mini(t_minishell *mini)
{
	ft_printf("\n| PID = %i\n", mini->main_pid);
	ft_printf("| pipe = %i\n", mini->pipe);
	ft_printf("| pipe_error = %i\n", mini->error_pipe);
	ft_printf("| redir_error = %i\n", mini->error_redir);
	ft_printf("| nb_cmd = %i\n", mini->nb_cmd);
	ft_printf("| redir_in = ");
	print_lst_redir(mini->redir_in);
	ft_printf("\n");
	ft_printf("| redir_out = ");
	print_lst_redir(mini->redir_out);
	ft_printf("\n\n");

	return (0);
}

int	print_lst(t_llist *lst)
{
	int i;

	i = 1;
	ft_printf("\n");
	while (lst != NULL)
	{
		ft_printf("token %i = %s;\n", i, lst->content);
		lst = lst->next;
		i++;
	}
	return (0);
}

int	print_cmd(char **cmd_line)
{
	int i = 0;
	while (cmd_line[i] != NULL)
	{
		ft_printf("%s ", cmd_line[i]);
		/* 		ft_printf("\narg 0 est: %s\n", mini->cmd_table[i][0]);
		ft_printf("arg 1 est: %s\n", mini->cmd_table[i][1]);
		ft_printf("arg 2 est: %s\n", mini->cmd_table[i][2]);
		ft_printf("arg 3 est: %s\n", mini->cmd_table[i][3]); */
		i++;
	}
	return (0);
}

int	print_cmd_table(t_minishell *mini, int cmd)
{
	int i = 0;

	while (i < cmd)
	{
		ft_printf("command %i = ", i);
		print_cmd(mini->cmd_table[i]);
		printf("\narg 0 est: %s\n", mini->cmd_table[i][0]);
		printf("arg 1 est: %s\n", mini->cmd_table[i][1]);
/* 		printf("arg 2 est: %s\n", mini->cmd_table[i][2]);
		printf("arg 3 est: %s\n", mini->cmd_table[i][3]); */
		ft_printf("\n");
		i++;
	}
	return (0);
}
