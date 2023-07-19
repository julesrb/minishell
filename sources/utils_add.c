/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_redir(t_redir **root, int type, char *str)
{
	t_redir	*new_node;
	t_redir	*curr;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (0);
	new_node->next = NULL;
	new_node->type = type;
	new_node->file = str;
	if (*root == NULL)
	{
		*root = new_node;
		return (1);
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
	return (1);
}

int	add_to_list(t_llist **root, char *str)
{
	t_llist	*new_node;
	t_llist	*curr;

	new_node = malloc(sizeof(t_redir));
	if (!str || !new_node)
		return (0);
	new_node->next = NULL;
	new_node->str = str;
	if (*root == NULL)
	{
		*root = new_node;
		return (1);
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
	return (1);
}
