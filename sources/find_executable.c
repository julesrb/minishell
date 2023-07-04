#include "minishell.h"

char    *ft_relative_path(char *cmd)
{
    char *relative_path = NULL;

    if (ft_strncmp(cmd, "./", 2) == 0)
        relative_path = ft_strjoin(getcwd(relative_path, ft_strlen(relative_path)), ft_strnstr(cmd, "./", ft_strlen(cmd)));
    return(relative_path);
}

int is_relative_path(char *path)
{
    if (strlen(path) >= 2 && (ft_strncmp(path, "./", 2) == 0 || ft_strncmp(path, "../", 3) == 0))
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

int is_absolute_path(char *path)
{
    if (ft_strlen(path) >= 1 && path[0] == '/')
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

char *find_executable(char **cmd)
{
    if (is_absolute_path(cmd[0]) == EXIT_SUCCESS)
        return(cmd[0]);
/*     else if(is_relative_path(cmd[0]) = EXIT_SUCCESS)
        return(ft_relative_path(cmd[0])); */
    else
        return(ft_access_path(cmd, 0));
    return (NULL);
}