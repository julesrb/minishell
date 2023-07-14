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
		free(curr->file);
		curr = curr->next;
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
		free(curr->content);
		curr = curr->next;
		free(trash);
	}
	*head = NULL;
}

void	free_tab_3d(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != NULL)
		{
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_mini(t_minishell *mini)
{
	if (mini->input != NULL)
		free(mini->input);
	if (mini->lexer_table != NULL)
		free_llist(&mini->lexer_table);
	if (mini->redir_start != NULL)
		free_redir(&mini->redir_start);
	if (mini->redir_end != NULL)
		free_redir(&mini->redir_end);
	if (mini->cmd_table != NULL)
		free_tab_3d(mini->cmd_table);
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
