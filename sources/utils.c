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

void	deallocate_list(t_llist **head)
{
	t_llist	*curr;
	t_llist	*trash;

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

void	free_mini(t_minishell *mini)
{
	int i;
	int j;

	i = 0;
	if (mini->cmd_table != NULL)
	{
		while (mini->cmd_table[i] != NULL)
		{
			j = 0;
			while (mini->cmd_table[i][j] != NULL)
			{
				free(mini->cmd_table[i][j]);
				j++;
			}
			free(mini->cmd_table[i]);
			i++;
		}
		free(mini->cmd_table);
	}
	if (mini->limiter != NULL)
		free(mini->limiter);
	if (mini->in_file != NULL)
		free(mini->in_file);
	if (mini->out_file != NULL)
		free(mini->out_file);
	if (mini->input != NULL)
		free(mini->input);

}

int	lst_size(t_llist *lst)
{
	int	size;

	size = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

