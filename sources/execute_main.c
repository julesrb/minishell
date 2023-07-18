/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:06:56 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/13 18:59:54 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **cmd, t_minishell *mini)
{
	if (!ft_strncmp(cmd[0], "pwd", max_length("pwd", cmd[0])))
		return (pwd_builtin(mini, cmd));
	else if (!ft_strncmp(cmd[0], "env", max_length("env", cmd[0])))
		return (env_builtin(mini));
	else if (!ft_strncmp(cmd[0], "cd", max_length("cd", cmd[0])))
		return (cd_builtin(cmd, mini, NULL));
	else if (!ft_strncmp(cmd[0], "export", max_length("export", cmd[0])))
		return (export_builtin(cmd, mini));
	else if (!ft_strncmp(cmd[0], "unset", max_length("unset", cmd[0])))
		return (unset_builtin(cmd, mini));
	else if (!ft_strncmp(cmd[0], "echo", max_length("echo", cmd[0])))
		return (echo_builtin(cmd));
	else if (!ft_strncmp(cmd[0], "exit", max_length("exit", cmd[0])))
		return (exit_builtin(cmd, mini));
	return (EXIT_FAILURE);
}

int	exec(char **cmd, char **envp, t_minishell *mini)
{
	char	*path;

	if (is_builtin(cmd[0]) == EXIT_SUCCESS)
		return (execute_builtin(cmd, mini));
	else
	{
		path = find_executable(cmd, mini);
		if (!path || (execve(path, cmd, envp) == -1))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free_success(path, NULL, NULL, NULL);
			return (127);
		}
	}
	return (EXIT_FAILURE);
}

int	exit_process(pid_t pid)
{
	int	status;
	int	exit_status;

	waitpid(pid, &status, 0);
	exit_status = WEXITSTATUS(status);
	if (WTERMSIG(status) == SIGINT)
		exit_status = 130;
	if (WTERMSIG(status) == SIGQUIT)
		exit_status = 131;
	return (exit_status);
}

int	executor(t_minishell *mini)
{
	pid_t	pid;
	int		status;

	if (mini->error == 1)
		return (0);
	signal_command(mini);
	if (mini->nb_cmd == 0)
	{
		pid = fork();
		if (pid == 0)
			exit(redirection_function(*mini, mini->redir_start));
		else
		{
			waitpid(pid, &status, 0);
			mini->exit_status = WEXITSTATUS(status);
		}
	}
	else if (mini->nb_cmd == 1)
		mini->exit_status = execute_one_cmd(mini);
	else
		mini->exit_status = exec_more_cmd(mini, 0, 0, 0);
	return (1);
}
