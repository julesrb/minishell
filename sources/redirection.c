#include "minishell.h"

void	here_doc_put_in(char *limiter, int *fds)
{
	char	*heredoc_line;

	close(fds[0]);
	while (1)
	{
		heredoc_line = readline("heredoc> ");
		if (ft_strncmp(heredoc_line, limiter, ft_strlen(limiter)) == 0)
		{
			free(heredoc_line);
			exit(EXIT_SUCCESS);
		}
		ft_putendl_fd(heredoc_line, fds[1]);
		free(heredoc_line);
	}
}

void	here_doc(char *limiter)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == EXIT_SUCCESS)
		here_doc_put_in(limiter, fds);
	else
	{
		wait(NULL);
		close(fds[1]);
		dup2(fds[0], 0);
	}
}

void	here_doc_insert(char *limiter)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == EXIT_SUCCESS)
		here_doc_put_in(limiter, fds);
	else
	{
		wait(NULL);
		close(fds[1]);
	}
}

int	input_redirection(t_minishell mini)
{
	int		fd_infile;
	t_redir	*redir;

	redir = mini.redir_in;
	if (!redir)
		return (EXIT_SUCCESS);
	if (redir->type == 1)
	{
		fd_infile = open(redir->file, O_RDONLY, 0777);
		if (fd_infile == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(redir->file);
			return (EXIT_FAILURE);
		}
		if (dup2(fd_infile, 0) == -1)
		{
			perror(NULL);
			return(EXIT_FAILURE);
		}
		close(fd_infile);
	}
	else if (redir->type == 2)
		here_doc(redir->file);
	return(EXIT_SUCCESS);
}

int	output_redirection(t_minishell mini)
{
	int		fd_outfile = 0;
	t_redir	*redir;

	redir = mini.redir_out;
	if (!redir)
		return (EXIT_SUCCESS);
	if (redir->type)
	{
		if (redir->type == 1)
		{
			fd_outfile = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return(EXIT_FAILURE);
			}
		}
		else if (redir->type == 2)
		{
			fd_outfile = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return(EXIT_FAILURE);
			}
		}
		if (dup2(fd_outfile, 1) == -1)
		{
			perror(NULL);
			return(EXIT_FAILURE);
		}
		close(fd_outfile);
	}
	return(EXIT_SUCCESS);
}

int	infile_insert(t_minishell mini)
{
	int fd_infile;

	t_redir	*redir;

	redir = mini.redir_in;
	if (!redir)
		return (EXIT_SUCCESS);
	if (redir->type == 1)
	{
		fd_infile = open(redir->file, O_RDONLY, 0777);
		if (fd_infile == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(redir->file);
			return (EXIT_FAILURE);
		}
		close(fd_infile);
	}
	else if (redir->type == 2)
		here_doc(redir->file);
	return(EXIT_SUCCESS);
}

int	outfile_insert(t_minishell mini)
{
	int fd_outfile = 0;
	t_redir	*redir;

	redir = mini.redir_out;
	if (!redir)
		return (EXIT_SUCCESS);
	if (redir->type)
	{
		if (redir->type == 1)
		{
			fd_outfile = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return(EXIT_FAILURE);
			}
		}
		else if (redir->type == 2)
		{
			fd_outfile = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return(EXIT_FAILURE);
			}
		}
		close(fd_outfile);
	}
	return(EXIT_SUCCESS);
}