/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:52:49 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/13 18:53:23 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir **head)
{
	t_redir	*curr;
	t_redir	*trash;

	curr = *head;
	while (curr != NULL)
	{
		trash = curr;
		curr = curr->next;
		free(trash->file);
		free(trash);
	}
	*head = NULL;
}

void	free_llist(t_llist **head)
{
	t_llist	*curr;
	t_llist	*trash;

	curr = *head;
	while (curr != NULL)
	{
		trash = curr;
		curr = curr->next;
		free(trash->str);
		free(trash);
	}
	*head = NULL;
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_tab_3d(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_free_tab(arr[i]);
		i++;
	}
	free(arr);
}
