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

t_llist	*parser_var_split(t_minishell *mini, t_llist **lex, t_llist *split_cmd)
{
	char	**split;
	int		i;

	i = 0;
	(*lex)->content = var_translation(mini, (*lex)->content);
	if (ft_strchr((*lex)->content, ' ') != NULL)
	{
		split = ft_split((*lex)->content, ' ');
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

t_llist	*parser_build_command(t_minishell *mini, int cmd, t_llist *lex)
{
	t_llist	*split_cmd;

	split_cmd = NULL;
	if (lex->content[0] == '|')
		lex = lex->next;
	while (lex != NULL && lex->content[0] != '|')
	{
		if (lex->content[0] == '<' || lex->content[0] == '>')
			lex = parser_redir_file(mini, lex, cmd, 0);
		if (lex != NULL && lex->content[0] == '$')
			split_cmd = parser_var_split(mini, &lex, split_cmd);
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
	free_llist(&split_cmd);
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
