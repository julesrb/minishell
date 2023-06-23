
#include "minishell.h"

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
	return (1);
}

void	ft_free_exit(char *str1, char *str2, char **tab1, char **tab2)
{
	perror(NULL);
	ft_free(str1, str2, tab1, tab2);
	exit(EXIT_FAILURE);
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

char	**ft_access_list_help(char *cmd_2, char **path_from_envp, int len, int i)
{
	char	**result;

	result = (char **)malloc(sizeof(result) * ++len);
	if (!result)
		ft_free_exit(cmd_2, NULL, NULL, path_from_envp);
	while (path_from_envp[i] != NULL)
	{
		result[i] = ft_strjoin(path_from_envp[i], cmd_2);
		if (!result[i])
			ft_free_exit(cmd_2, NULL, NULL, path_from_envp);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_access_list(char **cmd)
{
	int		len;
	char	**result;
    char    **path_from_envp;
    char    *cmd_2;

	len = 0;
	cmd_2 = (char *)malloc(sizeof(cmd_2) * (ft_strlen(cmd[0]) + 2));
	if (!cmd_2)
		ft_free_exit(NULL, NULL, cmd, NULL);
	cmd_2[0] = '/';
	ft_strlcpy(cmd_2 + 1, cmd[0], ft_strlen(cmd[0]) + 1);
	path_from_envp = ft_split(getenv("PATH"), ':');
	while (path_from_envp[len] != NULL)
		len++;
	result = ft_access_list_help(cmd_2, path_from_envp, len, 0);
	ft_free(cmd_2, NULL, NULL, path_from_envp);
	return (result);
}

char	*ft_access_path(char **cmd, int i)
{
	char	*result;
    char **access_list;

	result = NULL;
	access_list = ft_access_list(cmd);
	while (access_list[i] != NULL)
	{
		if (access(access_list[i], F_OK | X_OK) == 0)
		{
			result = malloc(sizeof(result) * ft_strlen(access_list[i]));
			if (!result)
				ft_free_exit(NULL, NULL, cmd, access_list);
			ft_strlcpy(result, access_list[i],
				ft_strlen(access_list[i]) + 1);
			break ;
		}
		i++;
	}
	ft_free_tab(access_list);
	return (result);
}


void    execute_command(char *input, char **envp)
{
    pid_t pid;
    char **cmd;
    char *path;

    pid = fork();
    if (pid == -1)
        exit(EXIT_FAILURE);
    if (pid == 0)
    {
        cmd = ft_split(input, ' ');
        path = ft_access_path(cmd, 0);
        if (!path)
        {   
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd[0], 2);
            ft_putendl_fd(": command not found", 2);
            exit(ft_free(path, NULL, cmd, NULL));
        }
        if(execve(path, cmd, envp) == -1)
        {   
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd[0], 2);
            ft_putendl_fd(": command not found", 2);
            exit(ft_free(path, NULL, cmd, NULL));
        }
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}