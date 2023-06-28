#include "minishell.h"

int     env_builtin(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
    {
        ft_putendl_fd(envp[i], 1);
        i++;
    }
    return(EXIT_SUCCESS);
}