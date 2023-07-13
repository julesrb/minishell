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
		type = 1;
	if (redir[0] == '>')
		type = 3;
	if (redir[0] == redir[1])
	{
		if (redir[0] == '<')
			type = 2;
		if (redir[0] == '>')
			type = 4;
	}
	return (type);
}

int	parser_redir_add_lst(t_minishell *mini, int type, char *file, int cmd_n)
{
	if (cmd == 0)
		add_to_redir(&mini->redir_start, type, ft_strdup(file));
	else
		add_to_redir(&mini->redir_end, type, ft_strdup(file));
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
		parser_redir_add_lst(mini, type, curr->content, cmd_n);
		return (curr->next);
	}
	return (curr);
}