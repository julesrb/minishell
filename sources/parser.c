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
		{
			ft_printf("ERROR FILE");
			mini->error_redir = 1;
		}
		i++;
	}
	if (mini->error_redir == 0)
	{
		if (mini->input_redirection == 1)
			mini->in_file = ft_strdup(curr->content);
		if (mini->input_redirection == 2)
			mini->limiter = ft_strdup(curr->content);
		if (mini->output_redirection != 0)
			mini->out_file = ft_strdup(curr->content);
		return (curr->next);
	}
	return (curr);
}

int	check_redirection(t_minishell *mini, char *redir, int cmd_nb)
{
	//ft_printf("HERE\n");
	if (cmd_nb == 0 || cmd_nb == mini->nb_cmd - 1) // edge case where in and out are inversed ?
	{
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
		if ((redir[0] == '<' && redir[1] == '>') ||
			(redir[0] == '>' && redir[1] == '<'))
			{
				ft_printf("redirection parser error.");
				mini->error_redir = 1;
			}
	}
	if (mini->input_redirection != 0 || mini->output_redirection != 0)
		return (1);
	return (0);
}

t_lexer	*build_command(t_minishell *mini, int cmd, t_lexer *lexer_pos)
{
	int arg;
	t_lexer	*curr;
	char *command;

	arg = 0;
	curr = lexer_pos;
	command = ft_strdup("");
	ft_printf("**\n");
	if (curr->content[0] == '|') // as first // as midle // as last // double
	{
		curr = curr->next;
	}
	while (curr != NULL && curr->content[0] != '|')
	{
		if (curr->content[0] == '<' || curr->content[0] == '>')
		{
			if (check_redirection(mini, curr->content, cmd) == 1)
				curr = check_redir_file(mini, curr);
		}
		command = ft_strjoin(command, curr->content);
		command = ft_strjoin(command, " ");
		ft_printf("+\n");
		curr = curr->next;
		ft_printf("-\n");
		arg++;
	}
	mini->cmd_table[cmd] = command;
	printf("command %i = %s\n", cmd, mini->cmd_table[cmd]);
	ft_printf("=\n");
	return (curr);
}

int	check_pipe_error(t_minishell *mini)
{
	t_lexer	*curr;
	
	curr = mini->lexer_table;

	if (curr->content[0] == '|') //check for pipe at begining
		mini->error_pipe = 1;
	//check for pipe at end begining

	while (curr != NULL)
	{
		if (curr->content[0] == '|')

		curr = curr->next;
	}
}

int	parser(t_minishell *mini)
{
	int cmd;
	t_lexer	*curr;
	
	cmd = 0;
	curr = mini->lexer_table;
	ft_printf("nb_CMD = %i\n", mini->pipe + 1);

	check_pipe_error(mini);
	mini->nb_cmd = mini->pipe + 1;
	mini->cmd_table = (char**)malloc(sizeof (char*) * (mini->nb_cmd));

	// translate_var_token(curr); // translate the var

	// check_redirection;
		// add the limiter option
	while (curr != NULL)
	{
		curr = build_command(mini, cmd, curr);
		cmd++;
	}
	//check_command();  and pipe;

	deallocate(&mini->lexer_table);
	ft_printf("Parser_done\n");
	return (1);
}
// redir error DONE
// pipe error
// command error or empty
// check redir first and last 
	//check redir file and asign