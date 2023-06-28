/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	print_cmd_table(t_minishell *t_mini, int cmd)
{
	int i = 0;

	while (i < cmd)
	{
		printf("command %i = %s\n", i, t_mini->cmd_table[i]);
		i++;
	}
	return (0);
}

/* int	translate_token(t_lexer *lexer)
{
	t_lexer *curr;

	curr = lexer;
	while (curr != NULL)
	{
		if (curr->content[0] == '')
	}
} */
int	check_redirection(t_minishell *t_mini, char *redir)
{
	if (redir[0] != redir[1])
	{
		if (redir[0] == '<')
			t_mini->input_redirection = 1;
		if (redir[0] == '>')
			t_mini->output_redirection = 1;
	}
	if (redir[0] == redir[1])
	{
		if (redir[0] == '<')
		{
			t_mini->input_redirection = 2;
			// add limiter;
			t_mini->limiter = "EOF";
		}
		if (redir[0] == '>')
			t_mini->output_redirection = 2;
	}
		// think about edge case like <> or ><
	return (0);
}

t_lexer	*build_command(t_minishell *t_mini, int cmd, t_lexer *lexer_pos)
{
	int arg;
	int a;
	t_lexer	*curr;
	char *command;

	arg = 0;
	a = 0;
	curr = lexer_pos;
	if (curr->content[0] == '|')
	{
		// check_double_pipe;
		curr = curr->next;
	}
	command = ft_strdup(curr->content);
	curr = curr->next;
	while (curr != NULL && curr->content[0] != '|')
	{
		if (curr->content[0] != '<' || curr->content[0] != '>')
			check_redirection(t_mini, curr->content);
		command = ft_strjoin(command, " ");
		command = ft_strjoin(command, curr->content);
		curr = curr->next;
		arg++;
	}
	t_mini->cmd_table[cmd] = command;
	return (curr);
}

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

int	parser(t_minishell *t_mini)
{
	int cmd;
	t_lexer	*curr;
	
	cmd = 0;
	curr = t_mini->lexer_table;
	t_mini->cmd_table = (char**)malloc(sizeof (char*) * t_mini->nb_cmd);

	// translate_var_token(curr); // translate the var

	// check_redirection;
		// add the limiter option
	while (curr != NULL)
	{
		curr = build_command(t_mini, cmd, curr);
		cmd++;
	}
	deallocate(&t_mini->lexer_table);
	print_cmd_table(t_mini, cmd);
	return (1);
}