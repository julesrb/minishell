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

t_lexer	*check_redir_file(t_minishell *mini, t_lexer *lexer_pos)
{
	t_lexer *curr;
	int i;

	i = 0;
	curr = lexer_pos;
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
		if (mini->input_redirection == -1 || mini->input_redirection == -2)
		{
			if (mini->input_redirection == -1)
				mini->in_file = ft_strdup(curr->content);
			else if (mini->input_redirection == -2)
				mini->limiter = ft_strdup(curr->content);
			mini->input_redirection -= mini->input_redirection * 2;
			return (curr->next);
		}
		if (mini->output_redirection != 0)
			mini->out_file = ft_strdup(curr->content);
		return (curr->next);
	}
	return (curr);
}

int	check_redirection(t_minishell *mini, char *redir, int cmd_nb)
{
	if (redir[0] == redir[1])
	{
		if (redir[0] == '<')
			mini->input_redirection = -2;
		if (redir[0] == '>')
			mini->output_redirection = 2;
	}
	else 
	{
		if (redir[0] == '<')
			mini->input_redirection = -1;
		if (redir[0] == '>')
			mini->output_redirection = 1;
	}
	if ((redir[0] == '<' && redir[1] == '>') ||
		(redir[0] == '>' && redir[1] == '<'))
		mini->error_redir = 1;
	if ((redir[0] == '<' && cmd_nb != 0)  ||
		(redir[0] == '>' && cmd_nb != mini->nb_cmd - 1))
		mini->error_redir = 1;
	if (mini->input_redirection != 0 || mini->output_redirection != 0)
		return (1);
	return (0);
}

t_lexer	*build_command(t_minishell *mini, int cmd, t_lexer *lexer_pos)
{
	t_lexer	*curr;
	char *command;

	curr = lexer_pos;
	command = ft_strdup("");
	if (curr->content[0] == '|')
		curr = curr->next;
	while (curr != NULL && curr->content[0] != '|')
	{
		if (curr->content[0] == '<' || curr->content[0] == '>')
		{
			if (check_redirection(mini, curr->content, cmd) == 1)
				curr = check_redir_file(mini, curr);
		}
		if (curr->content[0] == '$')
			var_translation(curr->content);
		if (curr != NULL && curr->content[0] != '|')
		{
			command = ft_strjoin(command, curr->content);
			command = ft_strjoin(command, " ");
			curr = curr->next;
		}
	}
	mini->cmd_table[cmd] = command;
	return (curr);
}

int	last_token_is_pipe(t_lexer *curr)
{
	while (curr->next != NULL)
		curr = curr->next;
	if (curr->content[0] == '|')
		return (1);
	return (0);
}

int	check_pipe_error(t_minishell *mini)
{
	t_lexer	*curr;
	
	curr = mini->lexer_table;
	if (curr->content[0] == '|') //check for pipe at begining
		mini->error_pipe = 1;
	if(last_token_is_pipe(curr) == 1)
		mini->error_pipe = 1;
	while (curr->next != NULL)
	{
		if (curr->content[0] == '|' && curr->next->content[0] == '|')
			mini->error_pipe = 1;
		curr = curr->next;
	}
	return(0);
}

int	parser(t_minishell *mini)
{
	int cmd;
	t_lexer	*curr;
	
	cmd = 0;
	curr = mini->lexer_table;
	check_pipe_error(mini);
	mini->nb_cmd = mini->pipe + 1;
	mini->cmd_table = (char**)malloc(sizeof (char*) * (mini->nb_cmd));

	// translate_var_token(curr); // translate the var

	while (curr != NULL)
	{
		curr = build_command(mini, cmd, curr);
		cmd++;
	}
	deallocate(&mini->lexer_table);
	return (1);
}

// command error or empty
// translate_var_token(curr); // translate the var