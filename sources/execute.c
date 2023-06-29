#include "minishell.h"

int	is_builtin(char *cmd)
{
	if(!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int		execute_builtin(char **cmd_split, char **envp)
{
	if(!ft_strncmp(cmd_split[0], "pwd", ft_strlen(cmd_split[0])))
		return (pwd_builtin());
	else if(!ft_strncmp(cmd_split[0], "env", ft_strlen(cmd_split[0])))
		return (env_builtin(envp));
/* 	else if(!ft_strncmp(cmd_split[0], "cd", ft_strlen(cmd_split[0])))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd_split[0], "export", ft_strlen(cmd_split[0])))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd_split[0], "unset", ft_strlen(cmd_split[0])))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd_split[0], "echo", ft_strlen(cmd_split[0])))
		return (EXIT_SUCCESS);
	else if(!ft_strncmp(cmd_split[0], "exit", ft_strlen(cmd_split[0])))
		return (EXIT_SUCCESS); */
	return(EXIT_FAILURE);
}


int	exec(char *cmd, char **envp)
{
	char **cmd_split;
    char *path;

        cmd_split = ft_split(cmd, ' ');
		if (is_builtin(cmd) == EXIT_SUCCESS)
		{
			if (!execute_builtin(cmd_split, envp))
			{
				ft_free_tab(cmd_split);
				exit(EXIT_SUCCESS);
			}
			ft_free_tab(cmd_split);
			exit(EXIT_FAILURE);
		}
		else
		{
			path = ft_access_path(cmd_split, 0);
			if (!path)
			{   
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd_split[0], 2);
				ft_putendl_fd(": command not found", 2);
				ft_free(path, NULL, cmd_split, NULL);
			}
			if(execve(path, cmd_split, envp) == -1)
			{   
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd_split[0], 2);
				ft_putendl_fd(": command not found", 2);
				ft_free(path, NULL, cmd_split, NULL);
			}
		}
	return(EXIT_FAILURE);
}

int	insert_pipe(char *cmd, char **envp)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			return(EXIT_FAILURE);
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
	return(EXIT_FAILURE);
}


int		execute_last_command(t_minishell mini, char **envp, int index)
{
	int fd[2];
	pid_t pid;
	int fd_outfile;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		if (mini.output_redirection)
		{
			fd_outfile = output_redirection(mini);
			if (fd_outfile == -1)
				perror(NULL);
			if (dup2(fd_outfile, 1) == -1)
				return(EXIT_FAILURE);
			close(fd_outfile);
		}
		exec(mini.cmd_table[index], envp);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		close(fd[0]);
		return(EXIT_SUCCESS);
	}
	return(EXIT_SUCCESS);
}


int    executor(t_minishell mini, char **envp)
{
	int index;
	int fd_infile = 0;

	if (mini.input_redirection)
	{
		if (mini.input_redirection == 1)
		{
			fd_infile = input_redirection(mini);
			if (dup2(fd_infile, 0) == -1)
				return(EXIT_FAILURE);
			close(fd_infile);
		}
		else if (mini.input_redirection == 2)
			here_doc(mini.limiter);
	}
	index = 0;
	while (index < mini.pipe)
	{
		insert_pipe(mini.cmd_table[index], envp);
		index++;
	}
	execute_last_command(mini, envp, index);
	return(EXIT_SUCCESS);
}