#include "minishell.h"

int	quote_translation(t_minishell *mini, t_llist *curr)
{
	int i;
	char *translation;
	char quote;

	i = 0;
	translation = NULL;
	(void)mini;
	quote = curr->content[0];
	if (quote == 34) // double quotes
	{
		//check for var
	}
	while (curr->content[i] != 0)
	{
		curr->content[i] = curr->content[i + 1];
		if (curr->content[i] == quote)
			curr->content[i] = 0;
		i++;
	}
	return(EXIT_SUCCESS);
}

int	var_translation(t_minishell *mini, t_llist *curr)
{
	int i;
	char *keyword;
	char *translation;

	i = 0;
	translation = NULL;
	if (curr->content[1] == 0)
		return(EXIT_SUCCESS);
	if (curr->content[1] == '?')
	{
		curr->content[0] = mini->exit_status + '0';
		curr->content[1] = 0;
		return(EXIT_SUCCESS);
	}
	keyword = ft_strdup(&curr->content[1]);
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