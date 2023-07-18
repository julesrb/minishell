/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_translation(t_minishell *mini, t_llist *curr)
{
	int		i;
	char	quote;
	char	flag_translation;

	i = 0;
	flag_translation = 0;
	(void)mini;
	quote = curr->str[0];
	if (quote == 34)
		flag_translation = 1;
	while (curr->str[i] != 0)
	{
		curr->str[i] = curr->str[i + 1];
		if (curr->str[i] == quote)
			curr->str[i] = 0;
		i++;
	}
	if (flag_translation == 1)
	{
		if (ft_strchr(curr->str, '$') != NULL)
			curr->str = add_var_translation(mini, curr->str);
	}
	return (EXIT_SUCCESS);
}

char	*var_find_translation(t_list *curr, char *var, char *translation)
{
	int		i;
	char	*keyword;

	i = 0;
	keyword = ft_strdup(&var[1]);
	while (keyword[i] != 0 && keyword[i] != ' ')
		i++;
	keyword[i] = 0;
	keyword = ft_strjoin(keyword, "=");
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, keyword, ft_strlen(keyword))
			== EXIT_SUCCESS)
		{
			translation = ft_strdup((char *)
					((char *)curr->content + ft_strlen(keyword)));
			break ;
		}
		curr = curr->next;
	}
	free(keyword);
	if (translation == NULL)
		return (ft_strdup(""));
	return (translation);
}

char	*var_translation(t_minishell *mini, char *var)
{
	char	*translation;

	translation = NULL;
	if (var[1] == 0)
		return (ft_strdup("$"));
	if (var[1] == '?')
		return (ft_itoa(mini->exit_status));
	translation = var_find_translation(mini->env_mini, var, translation);
	return (translation);
}

char	*add_var_translation(t_minishell *mini, char *str)
{
	int		i;
	char	*translation;

	i = 0;
	translation = NULL;
	while (str[i] != 0 && str[i] != '$')
		i++;
	translation = var_translation(mini, &str[i]);
	str[i] = 0;
	i++;
	while (str[i] != 0 && str[i] != ' ')
		i++;
	translation = ft_strjoin(translation, &str[i]);
	translation = ft_strjoin(str, translation);
	return (translation);
}
