/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:29:17 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/11 19:29:41 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_minishell *mini, char **cmd)
{
	t_list	*curr;
	int i;

	i = 0;
	while (cmd[i] != NULL)
		i++;
	if (i > 1)
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		return(EXIT_FAILURE);
	}
	curr = mini->env_mini;
	while (ft_strncmp(curr->content, "PWD=", 4) != 0)
		curr = curr->next;
	ft_putendl_fd(curr->content + 4, 1);
	return (EXIT_SUCCESS);
}
