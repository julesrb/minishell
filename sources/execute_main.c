/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:06:56 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/11 19:14:43 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **cmd_split, t_minishell *mini)
{
	if (ft_strncmp(cmd_split[0], "pwd", max_length("pwd", cmd_split[0])) == EXIT_SUCCESS)
		return (pwd_builtin(mini));
	else if (ft_strncmp(cmd_split[0], "env", max_length("env", cmd_split[0])) == EXIT_SUCCESS)
		return (env_builtin(mini));
	else if (!ft_strncmp(cmd_split[0], "cd", max_length("cd", cmd_split[0])))
		return (cd_builtin(cmd_split[1], mini));
	else if (ft_strncmp(cmd_split[0], "export", max_length("export", cmd_split[0])) == EXIT_SUCCESS)
		return (export_builtin(cmd_split, mini));
	else if (!ft_strncmp(cmd_split[0], "unset", max_length("unset", cmd_split[0])))
		return (unset_builtin(cmd_split, mini));
	else if (ft_strncmp(cmd_split[0], "echo", max_length("echo", cmd_split[0])) == EXIT_SUCCESS)
		return (echo_builtin(cmd_split));
	else if (!ft_strncmp(cmd_split[0], "exit", max_length("exit", cmd_split[0])))
		return (exit_builtin(cmd_split, mini));
	return (EXIT_FAILURE);
}

int	exec(char **cmd, char **envp, t_minishell *mini)
{
	char	*path;

	if (is_builtin(cmd[0]) == EXIT_SUCCESS)
		return(execute_builtin(cmd, mini));
	else
	{
		path = find_executable(cmd, mini);
		if (!path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, NULL, NULL);
			return(127);
		}
		else if (execve(path, cmd, envp) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, NULL, NULL);
			return(127);
		}
	}
	return (EXIT_FAILURE);
}

void	handler(int n)
{
	ft_putendl_fd("Quit in the child", 2);
	(void)n;
}

int	execute_single_command(t_minishell *mini)
{
	pid_t	pid;
	int		exit_status;
	int status;

	if (is_env_function(mini->cmd_table[0][0]) == EXIT_SUCCESS)
	{
		infile_insert(*mini);
		outfile_insert(*mini);
		exit_status = exec(mini->cmd_table[0], mini->envp, mini);
		return (exit_status);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			input_redirection(*mini);
			output_redirection(*mini);
			exit_status = exec(mini->cmd_table[0], mini->envp, mini);
			exit(exit_status);
		}
		else
		{
			waitpid(pid, &status, 0);
			exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);
}

int	execute_several_commands(t_minishell *mini)
{
	int	index;
	int	**fd;
	int exit_status = 0;
	int status;

	index = 0;
	fd = create_pipe(mini);
	while (index < mini->nb_cmd)
	{
		if ((is_env_function(mini->cmd_table[index][0]) == EXIT_SUCCESS) && (index == mini->nb_cmd - 1))
		{
			outfile_insert(*mini);
			close(fd[index - 1][0]);
			exit_status = exec(mini->cmd_table[index], mini->envp, mini);
		}
		else
			create_process_fd(mini->cmd_table[index], mini, index, fd);
		index++;
	}
	while (wait(&status) != -1)
	{
		exit_status = WEXITSTATUS(status);
/* 		printf("exit status is...%d\n", exit_status);
		if (WEXITSTATUS(status) && (index == mini->nb_cmd - 1))
		{
			exit_status = WEXITSTATUS(status);
			printf("Code de sortie du dernier processus fils : %d\n", exit_status);
		} */
	}
	return (exit_status);
}

int	executor(t_minishell *mini)
{
	int exit_status;

	exit_status = 0;
	if (!mini->cmd_table)
		return (EXIT_FAILURE);
	signal_command(mini);
	if (mini->nb_cmd == 1)
	{
		exit_status = execute_single_command(mini);
		return (exit_status);
	}
	else
	{
		exit_status = execute_several_commands(mini);
		return (exit_status);
	}
	return (EXIT_SUCCESS);
}
