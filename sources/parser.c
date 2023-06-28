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

/* t_lexer	*check_redir_file(t_minishell *mini, t_lexer *lexer_pos)
{
	t_lexer *curr;
	int i;

	i = 0;
	curr = lexer_pos;

	while (curr->content[i] != 0)
	{
		if (ft_isalpha(curr->content[i]) == 0 || curr->content[i] != '.')
		{
			ft_printf("ERROR FILE");

		}
		i++;
	}
	return (curr->next);
} */

int	check_redirection(t_minishell *mini, char *redir)
{
	ft_printf("HERE\n");
	if (redir[0] == redir[1])
	{
		if (redir[0] == '<')
			mini->input_redirection = 2;
		if (redir[0] == '>')
			mini->output_redirection = 2;
	}
	else 
	{
		if (redir[0] == '<')
			mini->input_redirection = 1;
		if (redir[0] == '>')
			mini->output_redirection = 1;
	}
		if (redir[0] == '<' && redir[1] == '>')
			ft_printf("redirection parser error.");
		if (redir[0] == '>' && redir[1] == '<')
			ft_printf("redirection parser error.");
		return (0);
}

t_lexer	*build_command(t_minishell *mini, int cmd, t_lexer *lexer_pos)
{
	int arg;
	t_lexer	*curr;
	char *command;

	arg = 0;
	curr = lexer_pos;
	if (curr->content[0] == '|')
	{
		if (curr->next != NULL)
			curr = curr->next;
	}
	command = ft_strdup(curr->content);
	curr = curr->next;
	while (curr != NULL && curr->content[0] != '|')
	{
		if (curr->content[0] == '<' || curr->content[0] == '>')
			check_redirection(mini, curr->content);
		command = ft_strjoin(command, " ");
		command = ft_strjoin(command, curr->content);
		curr = curr->next;
		arg++;
	}
	mini->cmd_table[cmd] = command;
	return (curr);
}


int	parser(t_minishell *mini)
{
	int cmd;
	t_lexer	*curr;
	
	cmd = 0;
	curr = mini->lexer_table;
	mini->cmd_table = (char**)malloc(sizeof (char*) * mini->nb_cmd);

	// translate_var_token(curr); // translate the var

	// check_redirection;
		// add the limiter option
	while (curr != NULL)
	{
		curr = build_command(mini, cmd, curr);
		cmd++;
	}
	//check_command();  and pipe;

	mini->nb_cmd = mini->pipe + 1;
	deallocate(&mini->lexer_table);
	ft_printf("Parser_done");
	return (1);
}
// redir error DONE
// pipe error
// command error or empty
// check redir first and last 
	//check redir file and asign