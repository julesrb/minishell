#include "minishell.h"

int	quote_translation(t_minishell *mini, t_llist *curr)
{
	int i;
	char quote;
	char flag_translation;

	i = 0;
	flag_translation = 0;
	(void)mini;
	quote = curr->content[0];
	if (quote == 34) // double quotes
		flag_translation = 1;
	while (curr->content[i] != 0)
	{
		curr->content[i] = curr->content[i + 1];
		if (curr->content[i] == quote)
			curr->content[i] = 0;
		i++;
	}
	if (flag_translation == 1)
	{
		if (ft_strchr(curr->content, '$') != NULL)
			add_var_translation(mini, curr->content);
	}
	return(EXIT_SUCCESS);
}

char	*var_translation2(t_minishell *mini, char *var)
{
	int i;
	char *keyword;
	char *translation;

	i = 0;
	translation = NULL;
	if (var[1] == 0)
		return(EXIT_SUCCESS);
	if (var[1] == '?')
	{
		var[0] = mini->exit_status + '0';
		var[1] = 0;
		return(EXIT_SUCCESS);
	}
	keyword = ft_strdup(&var[1]);
	while (mini->envp[i] != NULL)
	{
		if (ft_strncmp(mini->envp[i], keyword, ft_strlen(keyword)) == EXIT_SUCCESS)
		{
			translation = ft_strdup(&mini->envp[i][ft_strlen(keyword) + 1]);
		}
		i++;
	}
		free(keyword);
	free(curr->content);
	if (translation != NULL)
	{
		curr->content = translation;
	}
	else
		curr->content = ft_strdup(" ");
	return(EXIT_SUCCESS);
}

int	aad_var_translation(t_minishell *mini, char *str) // add var translation
{
	int i;
	char *keyword;
	char *translation;

	i = 0;
	translation = NULL;
	while (str[i] != 0 && str[i] != '$')
		i++;
	
	return(EXIT_SUCCESS);
}