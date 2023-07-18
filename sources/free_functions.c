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

void	free_redir(t_redir **head)
{
	t_redir	*curr;
	t_redir	*trash;

	curr = *head;
	while (curr != NULL)
	{
		trash = curr;
		curr = curr->next;
		free(trash->file);
		free(trash);
	}
	*head = NULL;
}

void	free_llist(t_llist **head)
{
	t_llist	*curr;
	t_llist	*trash;

	curr = *head;
	while (curr != NULL)
	{
		trash = curr;
		curr = curr->next;
		free(trash->str);
		free(trash);
	}
	*head = NULL;
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_tab_3d(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_free_tab(arr[i]);
		i++;
	}
	free(arr);
}

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

int	ft_free(char *str1, char *str2, char **tab1, char **tab2)
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

void	ft_free_exit(char *str1, char *str2, char **tab1, char **tab2)
{
	perror(NULL);
	ft_free(str1, str2, tab1, tab2);
	exit(EXIT_FAILURE);
}
