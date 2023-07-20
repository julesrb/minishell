/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:18 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/18 15:53:19 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_insert(t_minishell *mini, char *limiter)
{
	pid_t	pid;

	pid = fork();
	mini->here_doc_pid = pid;
	if (pid == -1)
		exit(0);
	if (pid == 0)
		here_doc_put_in_insert(limiter);
	else
	{
		waitpid(pid, NULL, 0);
	}
}

int	redirection_function_insert(t_minishell *mini, t_redir *redirection)
{
	int	exit_status;

	exit_status = 0;
	while (redirection != NULL)
	{
		if (redirection->type == 1 || redirection->type == 2)
			exit_status = infile_insert(mini, redirection);
		else if (redirection->type == 3 || redirection->type == 4)
			exit_status = outfile_insert(redirection, 0);
		if (exit_status == EXIT_FAILURE)
			break ;
		redirection = redirection->next;
	}
	return (exit_status);
}

int	infile_insert(t_minishell *mini, t_redir *start)
{
	int		fd_infile;

	(void)mini;
	if (!start)
		return (EXIT_SUCCESS);
	if (start->type == 1)
	{
		fd_infile = open(start->file, O_RDONLY, 0777);
		if (fd_infile == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(start->file);
			return (EXIT_FAILURE);
		}
		close(fd_infile);
	}
	else if (start->type == 2)
		here_doc_insert(mini, start->file);
	return (EXIT_SUCCESS);
}

int	outfile_insert(t_redir *end, int fd_outfile)
{
	if (!end)
		return (EXIT_SUCCESS);
	if (end->type)
	{
		if (end->type == 3)
		{
			fd_outfile = open(end->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return (EXIT_FAILURE);
			}
		}
		else if (end->type == 4)
		{
			fd_outfile = open(end->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return (EXIT_FAILURE);
			}
		}
		close(fd_outfile);
	}
	return (EXIT_SUCCESS);
}
