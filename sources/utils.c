/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_t_mini(t_minishell *t_mini)
{
	ft_printf("pipe = %i\n", t_mini->pipe);
	ft_printf("in_redir = %i\n", t_mini->input_redirection);
	ft_printf("out_redir = %i\n", t_mini->output_redirection);
	ft_printf("nb_cmd = %i\n", t_mini->nb_cmd);
	//ft_printf("input = %s\n",t_mini->cmd_table);
	return (0);
}

int	print_lst(t_lexer *lst)
{
	int i;

	i = 1;
	ft_printf("\n");
	while (lst != NULL)
	{
		printf("token %i = %s \n", i, lst->content);
		lst = lst->next;
		i++;
	}
	return (0);
}

void	deallocate(t_lexer **head)
{
	t_lexer	*curr;
	t_lexer	*trash;

	curr = *head;
	while (curr != NULL)
	{
		trash = curr;
		free(curr->content);
		curr = curr->next;
		free(trash);
	}
	*head = NULL;
}

int	print_cmd_table(t_minishell *t_mini, int cmd)
{
	int i = 0;

	while (i < cmd)
	{
		printf("command %i = %s\n", i, t_mini->cmd_table[i]);
		i++;
	}
	return (0);
}
