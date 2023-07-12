/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
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

t_llist	*parser_redir_file(t_minishell *mini, t_llist *lexer_pos, int cmd_nb)
{
	t_llist	*curr;
	int		i;
	int		type;

	i = 0;
	curr = lexer_pos;
	type = parser_redir_check(mini, curr->content, cmd_nb);
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
		if (type == 11 || type == 12)
		{
			if (type == 11)
				add_to_redir(&mini->redir_in, 1, ft_strdup(curr->content));
			else if (type == 12)
				add_to_redir(&mini->redir_in, 2, ft_strdup(curr->content));
		}
		if (type == 21 || type == 22)
		{
			if (type == 21)
				add_to_redir(&mini->redir_out, 1, ft_strdup(curr->content));
			else if (type == 22)
				add_to_redir(&mini->redir_out, 2, ft_strdup(curr->content));
		}
		return (curr->next);
	}
	return (curr);
}

char	**parser_malloc_command(t_llist *cmd_list)
{
	int		arg;
	int		i;
	char	**cmd_arr;
	t_llist	*cnt;

	i = 0;
	cnt = cmd_list;
	arg = lst_size(cnt);
	if (arg == 0)
	{
		cmd_arr = (char **)malloc(sizeof (char *) * 1);
		cmd_arr[0] = ft_strdup("");
	}
	else
	{
		cmd_arr = (char **)malloc(sizeof (char *) * (arg + 1));
		while (cmd_list != NULL)
		{
			cmd_arr[i] = ft_strdup(cmd_list->content);
			cmd_list = cmd_list->next;
			i++;
		}
		cmd_arr[i] = NULL;
	}
	return (cmd_arr);
}

t_llist	*parser_build_command(t_minishell *mini, int cmd, t_llist *lex)
{
	t_llist	*split_cmd;

	split_cmd = NULL;
	if (lex->content[0] == '|')
		lex = lex->next;
	while (lex != NULL && lex->content[0] != '|')
	{
		if (lex->content[0] == '<' || lex->content[0] == '>')
			lex = parser_redir_file(mini, lex, cmd);
		if (lex != NULL && lex->content[0] == '$')
		{
			lex->content = var_translation(mini, lex->content);
			lex = lex->next;
		}
		if (lex != NULL && (lex->content[0] == 34 || lex->content[0] == 39))
			quote_translation(mini, lex);
		if (lex != NULL && lex->content[0] != '|'
			&& lex->content[0] != '<' && lex->content[0] != '>')
		{
			add_to_list(&split_cmd, ft_strdup(lex->content));
			lex = lex->next;
		}
	}
	mini->cmd_table[cmd] = parser_malloc_command(split_cmd);
	deallocate_list(&split_cmd);
	return (lex);
}

int	parser(t_minishell *mini)
{
	int		cmd;
	t_llist	*lexer;

	cmd = 0;
	lexer = mini->lexer_table;
	if (!lexer)
		return (EXIT_FAILURE);
	if (mini->error_pipe == 0)
	{
		mini->nb_cmd = mini->pipe + 1;
		mini->cmd_table = (char ***)malloc
			(sizeof (char **) * (mini->nb_cmd + 1));
		if (!mini->cmd_table)
			return (EXIT_FAILURE);
		while (lexer != NULL)
		{
			lexer = parser_build_command(mini, cmd, lexer);
			cmd++;
		}
		if (mini->cmd_table[0][0][0] == 0)
			mini->nb_cmd = 0;
		mini->cmd_table[cmd] = NULL;
	}
	return (EXIT_SUCCESS);
}
