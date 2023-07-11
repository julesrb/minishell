#include "minishell.h"

int max_length(const char* str1, const char* str2) 
{
    size_t len1;
    size_t len2;

	len1 = ft_strlen(str1);
    len2 = ft_strlen(str2);
    if (len1 >= len2)
        return (len1);
    else
        return (len2);
}

int	is_builtin(char *cmd)
{
	if(ft_strncmp(cmd, "pwd", max_length("pwd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "env", max_length("env", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "cd", max_length("cd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "export", max_length("export", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "unset", max_length("unset", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "echo", max_length("echo", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "exit", max_length("exit", cmd)) == EXIT_SUCCESS)
	 	return (EXIT_SUCCESS); 
	return(EXIT_FAILURE);
}

int		execute_builtin(char **cmd_split, t_minishell *mini)
{
	if(ft_strncmp(cmd_split[0], "pwd", max_length("pwd", cmd_split[0])) == EXIT_SUCCESS)
		return (pwd_builtin(mini));
	else if(ft_strncmp(cmd_split[0], "env", max_length("env", cmd_split[0])) == EXIT_SUCCESS)
		return (env_builtin(mini));
	else if(!ft_strncmp(cmd_split[0], "cd", max_length("cd", cmd_split[0])))
		return (cd_builtin(cmd_split[1], mini));
	else if(ft_strncmp(cmd_split[0], "export", max_length("export", cmd_split[0])) == EXIT_SUCCESS)
		return (export_builtin(cmd_split, mini));
	else if(!ft_strncmp(cmd_split[0], "unset", max_length("unset", cmd_split[0])))
		return (unset_builtin(cmd_split, mini));
	 else if(ft_strncmp(cmd_split[0], "echo", max_length("echo", cmd_split[0])) == EXIT_SUCCESS)
	 	return (echo_builtin(cmd_split));
	else if(!ft_strncmp(cmd_split[0], "exit", max_length("exit", cmd_split[0])))
		return (exit_builtin(cmd_split, mini));
	return(EXIT_FAILURE);
}

int	exec(char **cmd, char **envp, t_minishell *mini)
{
    char *path;

	if (is_builtin(cmd[0]) == EXIT_SUCCESS)
	{
		if (execute_builtin(cmd, mini) == EXIT_SUCCESS)
			return(EXIT_SUCCESS);
		return(EXIT_FAILURE);
	}
	else
	{
		path = find_executable(cmd, mini);
		if (!path)
		{   
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, NULL, NULL);
		}
		else if(execve(path, cmd, envp) == -1)
		{   
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, NULL, NULL);
		}
	}
	return(EXIT_FAILURE);
}

int	create_process_fd(char **cmd, char **envp, t_minishell *mini, int index, int **fd)
{
	pid_t	pid;
	int i;

	i = 0;
	pid = fork();
	if (pid == -1)
		return(EXIT_FAILURE);
	if (pid == 0)
	{
		if (index == 0)
		{
			input_redirection(*mini);
			dup2(fd[index][1], 1);
		}
		else if (index == mini->nb_cmd - 1)
		{
			output_redirection(*mini);
			dup2(fd[index - 1][0], 0);
		}
		else
		{
			dup2(fd[index - 1][0], 0);
			dup2(fd[index][1], 1);
		}
		i = 0;
		while (fd[i] != NULL)
		{
			close(fd[i][0]);
			close(fd[i][1]);
			i++;
		}
		if (exec(cmd, envp, mini) == EXIT_SUCCESS)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (index == 0)
		{
			close(fd[index][1]);
		}
		else if (index == mini->nb_cmd - 1)
		{
			close(fd[index - 1][0]);				
		}
		else
		{
			close(fd[index - 1][0]);
			close(fd[index][1]);
		}
	}
	return(EXIT_SUCCESS);
}

int	is_env_function(char *cmd)
{
	if(ft_strncmp(cmd, "cd", max_length("cd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "export", max_length("export", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "unset", max_length("unset", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int    executor(t_minishell *mini, char **envp)
{
	int index;
	int **fd;
	int i;
	pid_t pid = 0;

	i = 0;
	index = 0;
	fd = NULL;
	if (mini->nb_cmd == 1)
	{
		if (is_env_function(mini->cmd_table[0][0]) == EXIT_SUCCESS)
		{
			infile_insert(*mini);
			outfile_insert(*mini);
			if (exec(mini->cmd_table[0], envp, mini) == EXIT_SUCCESS)
				return(EXIT_SUCCESS);
			return (EXIT_FAILURE);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				input_redirection(*mini);
				output_redirection(*mini);
				if (exec(mini->cmd_table[0], envp, mini) == EXIT_SUCCESS)
					exit(EXIT_SUCCESS);
			}
			else
				waitpid(pid, NULL, 0);
		}
	}
	else
	{
		fd = malloc(sizeof(int*) * (mini->nb_cmd));
		while(i < mini->nb_cmd - 1)
		{
			fd[i] = malloc(sizeof(int*) * 2);
			pipe(fd[i]);
			i++;
		}
		fd[i] = NULL;
		while (index < mini->nb_cmd)
		{
			create_process_fd(mini->cmd_table[index], envp, mini, index, fd);
			index++;
		}
		while (wait(NULL) != -1);
	}
	return(EXIT_SUCCESS);
}