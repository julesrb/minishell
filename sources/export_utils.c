/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:28:29 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/12 18:28:32 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrchr_set(const char *s, char *set)
{
	long	i;
	int		j;
	char	*str;

	str = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (str[i] == (set[j] % 256))
				return (str + i);
			j++;
		}
		i--;
	}
	return (NULL);
}

int	check_arg_export(char *export_arg)
{
	char	*var_name;
	int		i;

	i = 0;
	while (export_arg[i] && (export_arg[i] != '='))
		i++;
	var_name = (char *)malloc(sizeof(var_name) * i + 1);
	ft_strlcpy(var_name, export_arg, i + 1);
	if (ft_isalpha(export_arg[0]) == 0)
	{
		ft_putstr_fd("export: not an identifier: ", 2);
		ft_putendl_fd(export_arg, 2);
		return (EXIT_FAILURE);
	}
	else if (ft_strrchr_set(var_name, "$`\"'|><*?[]\\@#{}-+/^!()") != NULL)
	{
		ft_putstr_fd("export: not valid in this context: ", 2);
		ft_putendl_fd(export_arg, 2);
		return (ft_free_fail(var_name, NULL, NULL, NULL));
	}
	return (ft_free_success(var_name, NULL, NULL, NULL));
}

int	check_update_var(char *cmd, t_list *env_mini)
{
	int		i;
	t_list	*curr;

	i = 0;
	curr = env_mini;
	while (cmd[i] && (cmd[i] != '='))
		i++;
	while (curr != NULL)
	{
		if (strncmp(cmd, (char *)(curr->content), i) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		curr = curr->next;
	}
	return (EXIT_FAILURE);
}

int	list_env_update(t_minishell *mini, char *var_update)
{
	t_list	*curr;
	int		i;
	char	*new_var;

	i = 0;
	curr = mini->env_mini;
	while (var_update[i] && (var_update[i] != '='))
		i++;
	while (curr != NULL)
	{
		if (ft_strncmp(var_update, (char *)(curr->content), i) == EXIT_SUCCESS)
		{
			free(curr->content);
			new_var = ft_strdup(var_update);
			curr->content = (void *)new_var;
			return (EXIT_SUCCESS);
		}
		curr = curr->next;
	}
	return (EXIT_FAILURE);
}

char	*translate_var(t_minishell *mini, char *str)
{
	int		i;
	char	*translation;
	char	*temp;

	i = 0;
	translation = NULL;
	while (str[i] != 0 && str[i] != '$')
		i++;
	translation = var_translation(mini, &str[i]);
	str[i] = 0;
	i++;
	while (str[i] != 0 && str[i] != ' ')
		i++;
	temp = ft_strjoin(translation, &str[i]);
	translation = ft_strjoin(str, temp);
	free(temp);
	return (translation);
}
