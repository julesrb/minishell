/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parser_malloc_command(t_llist *cmd_list)
{
	int		arg;
	int		i;
	char	**cmd_arr;
	t_llist	*cnt;

	i = 0;
	cnt = cmd_list;
	arg = lst_size(cnt);
	MALLOC_OR_NULL(cmd_arr, sizeof (char *) * (arg + 1));
	while (cmd_list != NULL)
	{
		FT_STRDUP_OR_NULL(cmd_arr[i], cmd_list->str);
		cmd_list = cmd_list->next;
		i++;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

t_llist	*parser_var_split(t_minishell *mini, t_llist **lex, t_llist *split_cmd, int *m_err)
{
	char	**split;
	int		i;

	(void)m_err;
	i = 0;
	(*lex)->str = var_translation(mini, (*lex)->str);
	if (ft_strchr((*lex)->str, ' ') != NULL)
	{
		split = ft_split((*lex)->str, ' ');
		while (split[i] != NULL)
		{
			add_to_list(&split_cmd, ft_strdup(split[i]));
			i++;
		}
		ft_free_tab(split);
		*lex = (*lex)->next;
	}
	return (split_cmd);
}

t_llist	*parser_build_command(t_minishell *mini, int cmd, t_llist *lex, int *m_err)
{
	t_llist	*split_cmd;

	split_cmd = NULL;
	if (lex->str[0] == '|')
		lex = lex->next;
	while (lex != NULL && lex->str[0] != '|')
	{
		if (lex->str[0] == '<' || lex->str[0] == '>')
			lex = parser_redir_file(mini, lex, cmd, 0, m_err);
		if (lex != NULL && lex->str[0] == '$')
			split_cmd = parser_var_split(mini, &lex, split_cmd, m_err);
		if (lex != NULL && (lex->str[0] == 34 || lex->str[0] == 39))
			quote_translation(mini, lex);
		if (lex != NULL && lex->str[0] != '|' && lex->str[0] != '<' && lex->str[0] != '>')
		{
			if (!add_to_list(&split_cmd, ft_strdup(lex->str)))
			{
				*m_err = 1;
				return (NULL);
			}
			lex = lex->next;
		}
	}
	mini->cmd_table[cmd] = parser_malloc_command(split_cmd);
	if (!mini->cmd_table[cmd])
	{
		*m_err = 1;
		return (NULL); //review this shit
	}
	free_llist(&split_cmd);
	return (lex);
}

int	parser_last_token_is_pipe(t_llist *curr)
{
	while (curr->next != NULL)
		curr = curr->next;
	if (curr->str[0] == '|')
		return (1);
	return (0);
}

int	parser_error_pipe_check(t_minishell *mini)
{
	t_llist	*curr;

	curr = mini->lexer_table;
	if (curr->str[0] == '|')
		mini->error_pipe = 1;
	if (parser_last_token_is_pipe(curr) == 1)
		mini->error_pipe = 1;
	while (curr->next != NULL)
	{
		if (curr->str[0] == '|' && curr->next->str[0] == '|')
			mini->error_pipe = 1;
		curr = curr->next;
	}
	return (1);
}

int	parser_error_check(t_minishell *mini)
{
	parser_error_pipe_check(mini);
	if (mini->error_pipe == 1)
	{
		ft_failure("minishell: pipe error", 0, 1, 0);
		return (0);
	}
	if (mini->error_redir == 1)
	{
		ft_failure("minishell: redirection error", 0, 1, 0);
		return (0);
	}
	if (mini->nb_cmd == 0 && !mini->redir_start && !mini->redir_end)
	{
		ft_failure("minishell: parsing error", 0, 1, 0);
		return (0);
	}
	return (1);
}

int	parser(t_minishell *mini)
{
	int		cmd;
	int		malloc_err;
	t_llist	*lexer;

	cmd = 0;
	malloc_err = 0;
	lexer = mini->lexer_table;
	if (!parser_error_check(mini))
		return (1);
	MALLOC_OR_ZERO(mini->cmd_table, sizeof (char **) * (mini->nb_cmd + 1));
	while (lexer != NULL)
	{
		lexer = parser_build_command(mini, cmd, lexer, &malloc_err);
		if (malloc_err == 1)
			return (0);
		cmd++;
	}
	parser_error_check(mini);
	if (mini->cmd_table[0][0][0] == 0)
		mini->nb_cmd = 0;
	mini->cmd_table[cmd] = NULL;
	if (!mini->cmd_table)
		mini->error = 1;
	return (1);
}
