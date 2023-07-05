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
			curr->content = add_var_translation(mini, curr->content);
	}
	return(EXIT_SUCCESS);
}

char	*var_translation(t_minishell *mini, char *var)
{
	int i;
	char *keyword;
	char *translation;
	t_list *curr;

	i = 0;
	curr = mini->env_mini;
	translation = NULL;
	if (var[1] == 0)
		return(ft_strdup("$"));
	if (var[1] == '?')
	{
		translation[0] = mini->exit_status + '0';
		translation[1] = 0;
		return(ft_strdup(translation));
	}
	keyword = ft_strdup(&var[1]);
	while (keyword[i] != 0 && keyword[i] != ' ')
		i++;
	keyword[i] = 0;
	keyword = ft_strjoin(keyword, "=");
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, keyword, ft_strlen(keyword)) == EXIT_SUCCESS)
		{
			char *tmp = curr->content;
			translation = ft_strdup(&tmp[ft_strlen(keyword) + 1]);
		}
		curr = curr->next;
	}
	free(keyword);
	if (translation == NULL)
		return(ft_strdup(""));
	return(translation);
}

char	*add_var_translation(t_minishell *mini, char *str) // add var translation
{
	int i;
	char *translation;
	
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
	return(translation);
}