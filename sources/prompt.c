/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(t_minishell *mini)
{
	mini->input = readline("[Minishell] ");
	rl_redisplay();
	if (!mini->input)
	{
		free_mini(mini_global);
		if (mini_global->env_mini != NULL)
			deallocate_env(&mini_global->env_mini);
		exit (EXIT_SUCCESS);
	}
	if (mini->input[0] == 0)
		add_to_list(&mini->lexer_table, ft_strdup(""));
	else
		add_history(mini->input);
	return (EXIT_SUCCESS);
}
