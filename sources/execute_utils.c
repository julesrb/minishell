#include "minishell.h"

int max_length(const char* str1, const char* str2) 
{
    size_t len1;
    size_t len2;

	len1 = ft_strlen(str1);
    len2 = ft_strlen(str2);
    if (len1 >= len2)
        return (len1);
    else
        return (len2);
}

int	is_builtin(char *cmd)
{
	if(ft_strncmp(cmd, "pwd", max_length("pwd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "env", max_length("env", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "cd", max_length("cd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "export", max_length("export", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "unset", max_length("unset", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "echo", max_length("echo", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "exit", max_length("exit", cmd)) == EXIT_SUCCESS)
	 	return (EXIT_SUCCESS); 
	return(EXIT_FAILURE);
}

int	is_env_function(char *cmd)
{
	if(ft_strncmp(cmd, "cd", max_length("cd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "export", max_length("export", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "unset", max_length("unset", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return(EXIT_FAILURE);
}