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

int	check_redirection(t_minishell *mini, char *redir, int cmd_nb)
{
	int	type;

	type = 0;
	if (redir[0] == redir[1])
	{
		if (redir[0] == '<')
			type = 12;
		if (redir[0] == '>')
			type = 22;
	}
	if ((redir[0] == '<' && redir[1] == '>')
		|| (redir[0] == '>' && redir[1] == '<'))
		return (-1);
	if (redir[0] == '<')
		type = 11;
	if (redir[0] == '>')
		type = 21;
	if (cmd_nb != 0 || cmd_nb != mini->nb_cmd - 1)
		return (-1);
	return (type);
}

t_llist	*check_redir_file(t_minishell *mini, t_llist *lexer_pos, int cmd_nb)
{
	t_llist	*curr;
	int		i;
	int		type;

	i = 0;
	curr = lexer_pos;
	type = check_redirection(mini, curr->content, cmd_nb);
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
			if (type == 12)
				add_to_redir(&mini->redir_in, 2, ft_strdup(curr->content));
		}
		if (type == 21 || type == 22)
		{
			if (type == 21)
				add_to_redir(&mini->redir_in, 1, ft_strdup(curr->content));
			if (type == 22)
				add_to_redir(&mini->redir_in, 2, ft_strdup(curr->content));
		}
		return (curr->next);
	}
	return (curr);
}

char	**malloc_command(t_llist *cmd_list)
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
		cmd_arr = (char **)malloc(sizeof (char *) * arg + 1);
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

t_llist	*build_command(t_minishell *mini, int cmd, t_llist *curr)
{
	t_llist	*split_cmd;

	split_cmd = NULL;
	if (curr->content[0] == '|')
		curr = curr->next;
	while (curr != NULL && curr->content[0] != '|')
	{
		if (curr->content[0] == '<' || curr->content[0] == '>')
			curr = check_redir_file(mini, curr, cmd);
		if (curr != NULL && curr->content[0] == '$')
			curr->content = var_translation(mini, curr->content);
		if (curr != NULL && ((curr->content[0] == 34 || curr->content[0] == 39)))
			quote_translation(mini, curr);
		if (curr != NULL && curr->content[0] != '|'
			&& curr->content[0] != '<' && curr->content[0] != '>')
		{
			add_to_list(&split_cmd, ft_strdup(curr->content));
			curr = curr->next;
		}
	}
	mini->cmd_table[cmd] = malloc_command(split_cmd);
	deallocate_list(&split_cmd);
	return (curr);
}

int	last_token_is_pipe(t_llist *curr)
{
	while (curr->next != NULL)
		curr = curr->next;
	if (curr->content[0] == '|')
		return (1);
	return (0);
}

int	check_pipe_error(t_minishell *mini)
{
	t_llist	*curr;

	curr = mini->lexer_table;
	if (curr->content[0] == '|')
		mini->error_pipe = 1;
	if (last_token_is_pipe(curr) == 1)
		mini->error_pipe = 1;
	while (curr->next != NULL)
	{
		if (curr->content[0] == '|' && curr->next->content[0] == '|')
			mini->error_pipe = 1;
		curr = curr->next;
	}
	return (0);
}

int	parser(t_minishell *mini)
{
	int		cmd;
	t_llist	*curr;

	cmd = 0;
	curr = mini->lexer_table;
	check_pipe_error(mini);
	if (mini->error_pipe == 0)
	{
		mini->nb_cmd = mini->pipe + 1;
		mini->cmd_table = (char ***)malloc(sizeof (char **) * (mini->nb_cmd + 1));
		while (curr != NULL)
		{
			curr = build_command(mini, cmd, curr);
			cmd++;
		}
		if (mini->cmd_table[0][0][0] == 0)
			mini->nb_cmd = 0;
		mini->cmd_table[cmd] = NULL;
	}
	// if redir_in or _out are nto empty its still one command;
	deallocate_list(&mini->lexer_table);
	return (1);
}
