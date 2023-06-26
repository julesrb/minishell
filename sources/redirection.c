#include "minishell.h"

/* void	here_doc_put_in(char **av, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	here_doc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
} */


void handle_here_document(const char* delimiter)
{
    char* line = NULL;

    while (1)
    {
		line = get_next_line(0);
        if (strcmp(line, delimiter) == 0)
            break;
    }
    free(line);
}

int     input_redirection(t_minishell mini)
{
    int fd_infile;

    fd_infile = 0;
    if (mini.input_redirection == 0 || mini.input_redirection == 2)
        fd_infile = 0;
    else if (mini.input_redirection == 1)
    {
	    fd_infile = open(mini.cmd_table[0], O_RDONLY, 0777);
        if (fd_infile == -1)
	    {
            ft_putstr_fd("bash: ", 2);
            perror("file1");
            exit (EXIT_FAILURE);
    	}
    }
    else if (mini.input_redirection == 2)
        handle_here_document("EOF");
    return (fd_infile);
}

int     output_redirection(t_minishell mini)
{
    int fd_outfile;

    fd_outfile = 1;
    if (mini.output_redirection == 0)
        fd_outfile = 1;
    else if (mini.output_redirection == 1)
    {
	    fd_outfile = open(mini.cmd_table[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (fd_outfile == -1)
		    perror(NULL);
    }
    else if (mini.output_redirection == 2)
    {
	    fd_outfile = open(mini.cmd_table[3], O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (fd_outfile == -1)
		    perror(NULL);
    }
    return (fd_outfile);
}