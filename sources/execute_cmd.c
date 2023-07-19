/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:35:03 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/18 15:35:06 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_more_cmd(t_minishell *mini, int index, int exit_status, pid_t pid)
{
	int		**fd;

	fd = create_pipe(mini);
	while (index < mini->nb_cmd)
	{
		if ((is_env_function(mini->cmd_table[index]))
			&& (index == mini->nb_cmd - 1))
		{
			redirection_function_insert(*mini, mini->redir_end);
			close(fd[index - 1][0]);
			exit_status = exec(mini->cmd_table[index], mini->envp, mini);
		}
		else if (index == mini->nb_cmd - 1)
			pid = create_process_fd(mini->cmd_table[index], mini, index, fd);
		else
			create_process_fd(mini->cmd_table[index], mini, index, fd);
		index++;
	}
	if (pid)
		exit_status = exit_process(pid);
	while (wait(NULL) != -1)
		;
	free_pipe(fd);
	return (exit_status);
}

int	execute_one_cmd(t_minishell *mini)
{
	pid_t	pid;
	int		exit_status;

	if (is_env_function(mini->cmd_table[0]))
	{
		redirection_function_insert(*mini, mini->redir_start);
		exit_status = exec(mini->cmd_table[0], mini->envp, mini);
		return (exit_status);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			redirection_function(*mini, mini->redir_start);
			exit_status = exec(mini->cmd_table[0], mini->envp, mini);
			exit(exit_status);
		}
		else
			exit_status = exit_process(pid);
	}
	return (exit_status);
}
