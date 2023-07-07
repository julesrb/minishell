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

int	input_redirection(t_minishell mini)
{
	int fd_infile;

	if (mini.input_redirection == 1)
	{
		fd_infile = open(mini.in_file, O_RDONLY, 0777);
		if (fd_infile == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(mini.in_file);
			return (EXIT_FAILURE);
		}
		if (dup2(fd_infile, 0) == -1)
		{
			perror(NULL);
			return(EXIT_FAILURE);
		}
		close(fd_infile);
	}
	else if (mini.input_redirection == 2)
		here_doc(mini.limiter);
	return(EXIT_SUCCESS);
}

int	output_redirection(t_minishell mini)
{
	int fd_outfile = 0;

	(void)mini;
	if (mini.output_redirection)
	{
		if (mini.output_redirection == 1)
		{
			fd_outfile = open(mini.out_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return(EXIT_FAILURE);
			}
		}
		else if (mini.output_redirection == 2)
		{
			fd_outfile = open(mini.out_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
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