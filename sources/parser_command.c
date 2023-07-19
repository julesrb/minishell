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

char	**parser_malloc_command(t_minishell *mini, t_llist *cmd_list)
{
	int		arg;
	int		i;
	char	**cmd_arr;
	t_llist	*cnt;

	i = 0;
	cnt = cmd_list;
	arg = lst_size(cnt);
	cmd_arr = (char **)calloc(1, sizeof (char *) * (arg + 1));
	while (cmd_list != NULL)
	{
		cmd_arr[i] = ft_strdup(cmd_list->str);
		if (!cmd_arr[i])
		{
			mini->error_malloc = 1;
			return (NULL);
		}
		cmd_list = cmd_list->next;
		i++;
	}
	return (cmd_arr);
}

t_llist	*parser_pieces(t_minishell *mini, t_llist *lex, int cmd)
{
	t_llist	*split_cmd;

	split_cmd = NULL;
	while (lex != NULL && lex->str[0] != '|')
	{
		if (lex->str[0] == '<' || lex->str[0] == '>')
			lex = parser_redir_file(mini, lex, cmd, 0);
		if (lex != NULL && lex->str[0] == '$')
			split_cmd = parser_var_split(mini, &lex, split_cmd);
		if (lex != NULL && (lex->str[0] == 34 || lex->str[0] == 39))
			quote_translation(mini, lex);
		if (lex != NULL && lex->str[0] != '|'
			&& lex->str[0] != '<' && lex->str[0] != '>')
		{
			if (!add_to_list(&split_cmd, ft_strdup(lex->str)))
			{
				mini->error_malloc = 1;
				return (NULL);
			}
			lex = lex->next;
		}
	}
	return (split_cmd);
}

/* t_llist	*parser_build_command(t_minishell *mini, int cmd, t_llist *lex)
{
	t_llist	*split_cmd;

	split_cmd = NULL;
	if (lex->str[0] == '|')
		lex = lex->next;
	split_cmd = parser_pieces(mini, lex, cmd);
	mini->cmd_table[cmd] = parser_malloc_command(mini, split_cmd);
	if (!mini->cmd_table[cmd])
		mini->error_malloc = 1;
	free_llist(&split_cmd);
	return (lex);
}

t_llist	*parser_pieces(t_minishell *mini, t_llist *lex, int cmd)
{
	t_llist	*split_cmd;

	split_cmd = NULL;
	while (lex != NULL && lex->str[0] != '|')
	{
		if (lex->str[0] == '<' || lex->str[0] == '>')
			lex = parser_redir_file(mini, lex, cmd, 0);
		if (lex != NULL && lex->str[0] == '$')
			split_cmd = parser_var_split(mini, &lex, split_cmd);
		if (lex != NULL && (lex->str[0] == 34 || lex->str[0] == 39))
			quote_translation(mini, lex);
		if (lex != NULL && lex->str[0] != '|'
			&& lex->str[0] != '<' && lex->str[0] != '>')
		{
			if (!add_to_list(&split_cmd, ft_strdup(lex->str)))
			{
				mini->error_malloc = 1;
				return (NULL);
			}
			lex = lex->next;
		}
	}
	return (split_cmd);
}
 */
t_llist	*parser_build_cmd(t_minishell *mini, int i, t_llist *lex, t_llist *cmd)
{
	if (lex->str[0] == '|')
		lex = lex->next;
	while (lex != NULL && lex->str[0] != '|')
	{
		if (lex->str[0] == '<' || lex->str[0] == '>')
			lex = parser_redir_file(mini, lex, i, 0);
		if (lex != NULL && lex->str[0] == '$')
			cmd = parser_var_split(mini, &lex, cmd);
		if (lex != NULL && (lex->str[0] == 34 || lex->str[0] == 39))
			quote_translation(mini, lex);
		if (lex != NULL && lex->str[0] != '|'
			&& lex->str[0] != '<' && lex->str[0] != '>')
		{
			if (!add_to_list(&cmd, ft_strdup(lex->str)))
				mini->error_malloc = 1;
			lex = lex->next;
		}
	}
	mini->cmd_table[i] = parser_malloc_command(mini, cmd);
	if (!mini->cmd_table[i])
		mini->error_malloc = 1;
	if (mini->error_malloc == 1)
		return (NULL);
	free_llist(&cmd);
	return (lex);
}

int	parser_empty_cmd(t_minishell *mini)
{
	if (mini->cmd_table[0][0] == 0)
	{
		free_null(mini->cmd_table[0]);
		free_null(mini->cmd_table);
		mini->nb_cmd = 0;
		return (1);
	}
	if (!parser_error_check(mini))
		return (1);
	if (mini->cmd_table[0][0][0] == 0)
		mini->nb_cmd = 0;
	if (!mini->cmd_table)
		mini->error = 1;
	return (1);
}
