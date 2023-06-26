
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
            exit(ft_free(path, NULL, cmd, NULL));
        }
}

void	insert_pipe(char *cmd, char **envp)
{
	int	fd[2];
	int	pid;

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

void    executor(char *input, char **envp)
{
    pid_t pid;
	int index;
	int nb_cmd = 1;

	int fd_infile = open(pipex.argv[1], O_RDONLY, 0777);
	if (pipex.fd_infile == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(argv[1]);
		exit (EXIT_FAILURE);
	}
	if (dup2(pipex.fd_infile, 0) == -1)
		exit(EXIT_FAILURE);
	pipex.fd_outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex.fd_outfile == -1)
		perror(NULL);
	index = 2;
	while (index < argc -2)
		insert_pipe(pipex, index++);
	if (dup2(pipex.fd_outfile, 1) == -1)
		exit(EXIT_FAILURE);
	close(pipex.fd_outfile);
	exec(argv[argc - 2], pipex);


    pid = fork();
    if (pid == -1)
        exit(EXIT_FAILURE);
    if (pid == 0)
		exec(input, envp);
    else
        waitpid(pid, NULL, 0);
}