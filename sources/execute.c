#include "minishell.h"

int	is_builtin(char *cmd)
{
	if(ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "env", ft_strlen(cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	// else if(ft_strncmp(cmd, "cd", ft_strlen(cmd)) == EXIT_SUCCESS)
	// 	return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "export", ft_strlen(cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "unset", ft_strlen(cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "echo", ft_strlen(cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "exit", ft_strlen(cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS); 
	return(EXIT_FAILURE);
}

int		execute_builtin(char **cmd_split, t_minishell *mini)
{
	if(ft_strncmp(cmd_split[0], "pwd", ft_strlen(cmd_split[0])) == EXIT_SUCCESS)
		return (pwd_builtin());
	else if(ft_strncmp(cmd_split[0], "env", ft_strlen(cmd_split[0])) == EXIT_SUCCESS)
		return (env_builtin(mini));
	// else if(!ft_strncmp(cmd_split[0], "cd", ft_strlen(cmd_split[0])))
	// 	return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd_split[0], "export", ft_strlen(cmd_split[0])) == EXIT_SUCCESS)
		return (export_builtin(cmd_split, mini));
	// else if(!ft_strncmp(cmd_split[0], "unset", ft_strlen(cmd_split[0])))
	// 	return (EXIT_SUCCESS);
	// else if(!ft_strncmp(cmd_split[0], "echo", ft_strlen(cmd_split[0])))
	// 	return (EXIT_SUCCESS);
	// else if(!ft_strncmp(cmd_split[0], "exit", ft_strlen(cmd_split[0])))
	// 	return (EXIT_SUCCESS);
	return(EXIT_FAILURE);
}


int	exec(char *cmd, char **envp, t_minishell *mini)
{
	char **cmd_split;
    char *path;

	cmd_split = ft_split(cmd, ' ');
	if (is_builtin(cmd_split[0]) == EXIT_SUCCESS)
	{
		if (execute_builtin(cmd_split, mini) == EXIT_SUCCESS)
		{
			ft_free_tab(cmd_split);
			return(EXIT_SUCCESS);
		}
		ft_free_tab(cmd_split);
		return(EXIT_FAILURE);
	}
	else
	{
		if (ft_strchr(cmd_split[0], '/') != NULL)
			path = cmd_split[0];
		else
			path = ft_access_path(cmd_split, 0);
		if (!path)
		{   
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_split[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, cmd_split, NULL);
		}
		else if(execve(path, cmd_split, envp) == -1)
		{   
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_split[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, cmd_split, NULL);
		}
	}
	return(EXIT_FAILURE);
}

int	insert_pipe(char *cmd, char **envp, t_minishell *mini)
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
		exec(cmd, envp, mini);
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

int    executor(t_minishell *mini, char **envp)
{
	int index;
	pid_t pid;

	index = 0;
	pid = fork();
	if (pid == -1)
		return(EXIT_FAILURE);
	if (pid == 0)
	{
		if (input_redirection(*mini) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		while (index < mini->pipe)
			insert_pipe(mini->cmd_table[index++], envp, mini);
		if (output_redirection(*mini) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		exec(mini->cmd_table[index], envp, mini);
	}
	else	
		wait(NULL);
	return(EXIT_SUCCESS);
}