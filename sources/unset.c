/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:30:29 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/11 19:32:08 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_var(char *cmd, t_list *env_mini)
{
	while (env_mini != NULL)
	{
		if (ft_strncmp(cmd, (char *)(env_mini->content), strlen(cmd)) == 0)
			return (EXIT_SUCCESS);
		env_mini = env_mini->next;
	}
	return (EXIT_FAILURE);
}

int	lst_env_remove(t_minishell *mini, char *v_unset)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = mini->env_mini;
	while (curr != NULL)
	{
		if (!ft_strncmp(v_unset, (char *)(curr->content), ft_strlen(v_unset)))
		{
			if (prev == NULL)
				mini->env_mini = curr->next;
			else
				prev->next = curr->next;
			free(curr->content);
			free(curr);
			return (EXIT_SUCCESS);
		}
		prev = curr;
		curr = curr->next;
	}
	return (EXIT_FAILURE);
}

int	unset_builtin(char **cmd, t_minishell *mini)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	while (cmd[i] != NULL)
	{
		if (ft_strrchr_set(cmd[i], "$`\"'|><*?[]\\@#{}-+/^!()") != NULL)
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd(": invalid parameter name", 2);
			exit_status = 1;
		}
		else if (check_unset_var(cmd[i], mini->env_mini) == EXIT_SUCCESS)
		{
			lst_env_remove(mini, cmd[i]);
			exit_status = 0;
		}
		i++;
	}
	if (i == 1)
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		exit_status = 1;
	}
	return (exit_status);
}
