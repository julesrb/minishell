/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:17:31 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/11 19:20:19 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_pipe(t_minishell *mini)
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc(sizeof(int *) * (mini->nb_cmd));
	while (i < mini->nb_cmd - 1)
	{
		fd[i] = malloc(sizeof(int *) * 2);
		pipe(fd[i]);
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

int	close_fd(int **fd)
{
	int	i;

	i = 0;
	while (fd[i] != NULL)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	child_process(t_minishell *mini, int index, char **cmd, int **fd)
{
	if (index == 0)
	{
		redirection_function(*mini, mini->redir_start);
		dup2(fd[index][1], 1);
	}
	else if (index == mini->nb_cmd - 1)
	{
		redirection_function(*mini, mini->redir_end);
		dup2(fd[index - 1][0], 0);
	}
	else
	{
		dup2(fd[index - 1][0], 0);
		dup2(fd[index][1], 1);
	}
	close_fd(fd);
	mini->exit_status = exec(cmd, mini->envp, mini);
	exit(mini->exit_status);
}

pid_t	create_process_fd(char **cmd, t_minishell *mini, int index, int **fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		child_process(mini, index, cmd, fd);
	else
	{
		if (index == 0)
			close(fd[index][1]);
		else if (index == mini->nb_cmd - 1)
			close(fd[index - 1][0]);
		else
		{
			close(fd[index - 1][0]);
			close(fd[index][1]);
		}
	}
	return (pid);
}
