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
		return (cd_builtin(cmd, mini));
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
		if (!path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, NULL, NULL);
			return (127);
		}
		else if (execve(path, cmd, envp) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, NULL, NULL);
			return (127);
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
	int		status;

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

int	execute_several_commands(t_minishell *mini, int index)
{
	int		**fd;
	int		exit_status;
	int		status;
	int		exit_status2;
	pid_t	pid;

	pid = 0;
	exit_status = 0;
	exit_status2 = 0;
	fd = create_pipe(mini);
	while (index < mini->nb_cmd)
	{
		if ((is_env_function(mini->cmd_table[index][0]) == 0)
			&& (index == mini->nb_cmd - 1))
		{
			outfile_insert(*mini);
			close(fd[index - 1][0]);
			exit_status2 = exec(mini->cmd_table[index], mini->envp, mini);
		}
		else if (index == mini->nb_cmd - 1)
			pid = create_process_fd(mini->cmd_table[index], mini, index, fd);
		else
			create_process_fd(mini->cmd_table[index], mini, index, fd);
		index++;
	}
	if (pid != 0)
	{
		waitpid(pid, &status, 0);
		exit_status = WEXITSTATUS(status);
	}
	while (wait(NULL) != -1)
		;
	if ((is_env_function(mini->cmd_table[mini->nb_cmd - 1][0]) == EXIT_SUCCESS))
		return (exit_status2);
	return (exit_status);
}

/* int	input_redir(t_minishell mini, t_redir *start)
{
	int		fd_infile;

	if (!start)
		return (EXIT_SUCCESS);
	if (start->type == 1)
	{
		fd_infile = open(start->file, O_RDONLY, 0777);
		if (fd_infile == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(start->file);
			return (EXIT_FAILURE);
		}
		if (dup2(fd_infile, 0) == -1)
		{
			perror(NULL);
			return (EXIT_FAILURE);
		}
		close(fd_infile);
	}
	else if (start->type == 2)
		here_doc(start->file, mini);
	return (EXIT_SUCCESS);
}

int	output_redir(t_redir *end)
{
	int		fd_outfile ;

	fd_outfile = 0;
	if (!end)
		return (EXIT_SUCCESS);
	if (end->type)
	{
		if (end->type == 1)
		{
			fd_outfile = open(end->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return (EXIT_FAILURE);
			}
		}
		else if (end->type == 2)
		{
			fd_outfile = open(end->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (fd_outfile == -1)
			{
				perror(NULL);
				return (EXIT_FAILURE);
			}
		}
		if (dup2(fd_outfile, 1) == -1)
		{
			perror(NULL);
			return (EXIT_FAILURE);
		}
		close(fd_outfile);
	}
	return (EXIT_SUCCESS);
} */


int	executor(t_minishell *mini)
{
	int	exit_status;
	// t_redir	*curr = NULL;
	// pid_t pid;
	// int i = 0;

	exit_status = 0;
	if (!mini->cmd_table)
		return (EXIT_FAILURE);
	signal_command(mini);
/* 	if (mini->nb_cmd == 0)
	{
		curr = mini->redir_start;
		while(curr != NULL)
		{
			printf("%d: redir in %s\n", i, mini->redir_start->file);
			curr = curr->next;
			i++;
		}
		curr = mini->redir_end;
		i =  0;
		while(curr != NULL)
		{
			printf("%d: redir out %s\n", i, mini->redir_end->file);
			curr = curr->next;
			i++;
		}
		pid = fork();
		if (pid == 0)
		{
			curr = mini->redir_start;
			while(curr != NULL)
			{
				printf("test\n");
				input_redir(*mini, curr);
				curr = curr->next;
			}
			curr = mini->redir_end;
			while(curr != NULL)
			{
				printf("test\n");
				output_redir(curr);
				curr = curr->next;
			}
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, NULL, 0);
		return(EXIT_SUCCESS);
	} */
	if (mini->nb_cmd == 1)
	{
		exit_status = execute_single_command(mini);
		return (exit_status);
	}
	else
	{
		exit_status = execute_several_commands(mini, 0);
		return (exit_status);
	}
	return (EXIT_SUCCESS);
}
