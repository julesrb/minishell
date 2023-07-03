#include "minishell.h"

int	var_translation(t_minishell *mini, t_lexer *curr)
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