#include "minishell.h"

void	here_doc_put_in(char *limiter, int *fds)
{
	char	*ret;

	close(fds[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, limiter, ft_strlen(limiter)) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, fds[1]);
		free(ret);
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
	if (!pid)
		here_doc_put_in(limiter, fds);
	else
	{
		wait(NULL);
		close(fds[1]);
		dup2(fds[0], 0);
	}
}

int     input_redirection(t_minishell mini)
{
    int fd_infile;

    fd_infile = 0;
    if (mini.input_redirection == 1)
    {
	    fd_infile = open(mini.infile, O_RDONLY, 0777);
        if (fd_infile == -1)
	    {
            ft_putstr_fd("bash: ", 2);
            perror(mini.infile);
            exit (EXIT_FAILURE);
    	}
    }
    return (fd_infile);
}

int     output_redirection(t_minishell mini)
{
    int fd_outfile;

    fd_outfile = 1;
    if (mini.output_redirection == 1)
    {
	    fd_outfile = open(mini.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (fd_outfile == -1)
		    perror(NULL);
    }
    else if (mini.output_redirection == 2)
    {
	    fd_outfile = open(mini.outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (fd_outfile == -1)
		    perror(NULL);
    }
    return (fd_outfile);
}