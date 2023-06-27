
#include "minishell.h"

void	exec(char *cmd, char **envp)
{
	char **cmd_split;
    char *path;

        cmd_split = ft_split(cmd, ' ');
        path = ft_access_path(cmd_split, 0);
        if (!path)
        {   
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd_split[0], 2);
            ft_putendl_fd(": command not found", 2);
            exit(ft_free(path, NULL, cmd_split, NULL));
        }
        if(execve(path, cmd_split, envp) == -1)
        {   
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd_split[0], 2);
            ft_putendl_fd(": command not found", 2);
            exit(ft_free(path, NULL, cmd_split, NULL));
        }
}

void	insert_pipe(char *cmd, char **envp)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			exit(EXIT_FAILURE);
		close(fd[1]);
		exec(cmd, envp);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

void    executor(t_minishell mini, char **envp)
{
	int index;
	int fd_infile = 0;
	int fd_outfile = 1;


	if (mini.input_redirection != 2)
	{
		fd_infile = input_redirection(mini);
		if (dup2(fd_infile, 0) == -1)
			exit(EXIT_FAILURE);
	}
	else if (mini.input_redirection == 2)
	{
		here_doc("EOF");
	}
	fd_outfile = output_redirection(mini);
	index = 1;
	while (index < 1 + mini.pipe)
	{
		insert_pipe(mini.cmd_table[index], envp);
		index++;
	}
	if (dup2(fd_outfile, 1) == -1)
		exit(EXIT_FAILURE);
	if (fd_outfile != 1)
		close(fd_outfile);
	exec(mini.cmd_table[index], envp);
}