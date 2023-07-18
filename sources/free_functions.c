/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:52:49 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/13 18:53:23 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void *ptr)
{
	ptr = NULL;
	free(ptr);
}

void	free_mini(t_minishell *mini)
{
	if (mini->input != NULL)
		free_null(mini->input);
	if (mini->lexer_table != NULL)
	{
		free_llist(&mini->lexer_table);
	}
	if (mini->redir_start != NULL)
		free_redir(&mini->redir_start);
	if (mini->redir_end != NULL)
		free_redir(&mini->redir_end);
	if (mini->cmd_table != NULL)
		free_tab_3d(mini->cmd_table);
}

int	ft_free_fail(char *str1, char *str2, char **tab1, char **tab2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (tab1)
		ft_free_tab(tab1);
	if (tab2)
		ft_free_tab(tab2);
	return (EXIT_FAILURE);
}

int	ft_free_success(char *str1, char *str2, char **tab1, char **tab2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (tab1)
		ft_free_tab(tab1);
	if (tab2)
		ft_free_tab(tab2);
	return (EXIT_SUCCESS);
}

void	*ft_free_pointer(char *str1, char *str2, char **tab1, char **tab2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (tab1)
		ft_free_tab(tab1);
	if (tab2)
		ft_free_tab(tab2);
	return (NULL);
}
