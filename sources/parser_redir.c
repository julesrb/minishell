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
	if (cmd_n == 0)
	{
		if (!add_to_redir(&mini->redir_start, type, ft_strdup(file)))
			return (0);
	}
	else
	{
		if (!add_to_redir(&mini->redir_end, type, ft_strdup(file)))
			return (0);
	}
	return (1);
}

t_llist	*parser_redir_file(t_minishell *mini, t_llist *lex, int cm_n, int type)
{
	t_llist	*curr;
	int		i;

	i = 0;
	curr = lex;
	type = parser_redir_check(mini, curr->str, cm_n);
	if (type == -1 || curr->next == NULL)
	{
		mini->error_redir = 1;
		return (NULL);
	}
	else
		curr = curr->next;
	while (curr->str[i] != 0)
	{
		if (ft_isalnum(curr->str[i]) == 0 && curr->str[i] != '.')
			mini->error_redir = 1;
		i++;
	}
	if (mini->error_redir == 0)
	{
		parser_redir_add_lst(mini, type, curr->str, cm_n);
		return (curr->next);
	}
	return (curr);
}
