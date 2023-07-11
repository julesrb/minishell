#include "minishell.h"

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

int  execute_single_command(t_minishell *mini)
{
	pid_t pid = 0;

	if (is_env_function(mini->cmd_table[0][0]) == EXIT_SUCCESS)
	{
		infile_insert(*mini);
		outfile_insert(*mini);
		if (exec(mini->cmd_table[0], mini->envp, mini) == EXIT_SUCCESS)
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
			if (exec(mini->cmd_table[0], mini->envp, mini) == EXIT_SUCCESS)
				exit(EXIT_SUCCESS);
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, NULL, 0);
	}
	return (EXIT_SUCCESS);
}


int		execute_several_commands(t_minishell *mini)
{
	int index;
	int **fd;

	index = 0;
	fd = create_pipe(mini);
	while (index < mini->nb_cmd)
	{
		if ((is_env_function(mini->cmd_table[index][0]) == EXIT_SUCCESS) && (index == mini->nb_cmd - 1))
		{
			outfile_insert(*mini);
			close(fd[index - 1][0]);				
			if (exec(mini->cmd_table[index], mini->envp, mini) == EXIT_SUCCESS)
				return(EXIT_SUCCESS);
			return (EXIT_FAILURE);
		}
		else
			create_process_fd(mini->cmd_table[index], mini, index, fd);
		index++;
	}
	while (wait(NULL) != -1);
	return (EXIT_SUCCESS);
}

int    executor(t_minishell *mini)
{
	if (mini->nb_cmd == 1)
	{
		if (execute_single_command(mini) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	else
	{
		if (execute_several_commands(mini) == EXIT_SUCCESS)
			return(EXIT_SUCCESS);
	}
	return(EXIT_SUCCESS);
}