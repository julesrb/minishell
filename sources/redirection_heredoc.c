#include "minishell.h"

char	*ft_reverse_split(char **line_split, char *c)
{
	char *result;
	int i;
	char *temp;

	temp = NULL;
	i = 1;
	result = ft_strdup(line_split[0]);
	while(line_split[i] != NULL)
	{
		temp = ft_strdup(line_split[i]);
		result = ft_strjoin(result, c);
		result = ft_strjoin(result, temp);
		free(temp);
		i++;
	}
	return(result);
}

int	ft_strlcpy_dollar(char *str, t_minishell mini)
{
	char	*temp;
	char	*temp2;

	temp = ft_strtrim(str, "\'\".");
	temp2 = getenv_mini(temp + 1, &mini);
	free(temp);
	if (temp2 != NULL)
	{
		free(str);
		str = malloc(sizeof(char) * (ft_strlen(temp2) + 1));
		ft_strlcpy(str, temp2, ft_strlen(temp2) + 1);
	}
	else
	{
		free(str);
		str = malloc(sizeof(char) * 1);
		ft_strlcpy(str, (char *)"\0", 1);
	}
	return(EXIT_SUCCESS);
}

char	*heredoc_convert_dollar(t_minishell mini, char *line)
{
	char	 **line_split;
	char	*result;
	char	*env_val;
	int i;

	i = 0;
	env_val = ft_strtrim(line, "\'\".");
	line_split = ft_split(env_val, ' ');
	if (!line_split)
		return (NULL);
	free(env_val);
	while(line_split[i] != NULL)
	{
		if (ft_strchr(line_split[i], '$') != NULL)
			ft_strlcpy_dollar(line_split[i], mini);
		i++;
	}
	result = ft_reverse_split(line_split, (char *)" ");
	ft_free_success(NULL, NULL, line_split, NULL);
	return (result);
}


void	here_doc_put_in(char *limiter, int *fds, t_minishell mini)
{
	char	*heredoc_line;
	char	*heredoc_line2;

	close(fds[0]);
	while (1)
	{
		heredoc_line = readline("heredoc> ");
		if (ft_strncmp(heredoc_line, limiter, ft_strlen(limiter)) == 0)
		{
			free(heredoc_line);
			exit(EXIT_SUCCESS);
		}
		if (ft_strrchr(heredoc_line, '$') != NULL)
			heredoc_line2 = heredoc_convert_dollar(mini, heredoc_line);
		else
			heredoc_line2 = ft_strdup(heredoc_line);
		ft_putendl_fd(heredoc_line2, fds[1]);
		ft_free_success(heredoc_line, heredoc_line2, NULL, NULL);
	}
}