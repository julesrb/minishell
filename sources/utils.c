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

void	free_mini(t_minishell *mini)
{
	int i;

	i = 0;
	if (mini->cmd_table != NULL)
	{
		while (i < mini->nb_cmd)
		{
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


