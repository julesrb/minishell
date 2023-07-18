/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:06:50 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/13 19:06:51 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limiter, t_minishell mini)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == EXIT_SUCCESS)
		here_doc_put_in(limiter, fds, mini);
	else
	{
		wait(NULL);
		close(fds[1]);
		dup2(fds[0], 0);
	}
}

int	redirection_function(t_minishell mini, t_redir *redirection)
{
	int	exit_status;

	exit_status = 0;
	while (redirection != NULL)
	{
		if (redirection->type == 1 || redirection->type == 2)
			exit_status = input_redirection(mini, redirection);
		else if (redirection->type == 3 || redirection->type == 4)
			exit_status = output_redirection(redirection, 0);
		if (exit_status == EXIT_FAILURE)
			break ;
		redirection = redirection->next;
	}
	return (exit_status);
}

int	input_redirection(t_minishell mini, t_redir *start)
{
	int		fd_infile;

	if (!start)
		return (EXIT_SUCCESS);
	if (start->type == 1)
	{
		fd_infile = open(start->file, O_RDONLY, 0777);
		if (fd_infile == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(start->file);
			exit (EXIT_FAILURE);
		}
		if (dup2(fd_infile, 0) == -1)
		{
			perror(NULL);
			return (EXIT_FAILURE);
		}
		close(fd_infile);
	}
	else if (start->type == 2)
		here_doc(start->file, mini);
	return (EXIT_SUCCESS);
}

void	exit_redir(int fd_outfile)
{
	if (fd_outfile == -1)
	{
		perror(NULL);
		exit (EXIT_FAILURE);
	}
}

int	output_redirection(t_redir *end, int fd_outfile)
{
	if (!end)
		return (EXIT_SUCCESS);
	if (end->type)
	{
		if (end->type == 3)
		{
			fd_outfile = open(end->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			exit_redir(fd_outfile);
		}
		else if (end->type == 4)
		{
			fd_outfile = open(end->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
			exit_redir(fd_outfile);
		}
		if (dup2(fd_outfile, 1) == -1)
		{
			perror(NULL);
			return (EXIT_FAILURE);
		}
		close(fd_outfile);
	}
	return (EXIT_SUCCESS);
}
