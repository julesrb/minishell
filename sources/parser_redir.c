/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_redir_check(t_minishell *mini, char *redir, int cmd_nb)
{
	int	type;

	type = 0;
	if (cmd_nb != (mini->nb_cmd - 1) && cmd_nb != 0)
		return (-1);
	if ((redir[0] == '<' && redir[1] == '>')
		|| (redir[0] == '>' && redir[1] == '<'))
		return (-1);
	if (redir[0] == '<')
		type = 11;
	if (redir[0] == '>')
		type = 21;
	if (redir[0] == redir[1])
	{
		if (redir[0] == '<')
			type = 12;
		if (redir[0] == '>')
			type = 22;
	}
	return (type);
}

int	parser_redir_add_lst(t_minishell *mini, int type, char *file)
{
	if (type == 11 || type == 12)
	{
		if (type == 11)
			add_to_redir(&mini->redir_in, 1, ft_strdup(file));
		else if (type == 12)
			add_to_redir(&mini->redir_in, 2, ft_strdup(file));
	}
	if (type == 21 || type == 22)
	{
		if (type == 21)
			add_to_redir(&mini->redir_out, 1, ft_strdup(file));
		else if (type == 22)
			add_to_redir(&mini->redir_out, 2, ft_strdup(file));
	}
	return (EXIT_SUCCESS);
}

t_llist	*parser_redir_file(t_minishell *mini, t_llist *lex, int cmd_n, int type)
{
	t_llist	*curr;
	int		i;

	i = 0;
	curr = lex;
	type = parser_redir_check(mini, curr->content, cmd_n);
	if (type == -1)
	{
		mini->error_redir = 1;
		return (curr);
	}
	if (curr->next != NULL)
		curr = curr->next;
	while (curr->content[i] != 0)
	{
		if (ft_isalnum(curr->content[i]) == 0 && curr->content[i] != '.')
			mini->error_redir = 1;
		i++;
	}
	if (mini->error_redir == 0)
	{
		parser_redir_add_lst(mini, type, curr->content);
		return (curr->next);
	}
	return (curr);
}
