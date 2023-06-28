#include "minishell.h"

int     env_builtin(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return(EXIT_SUCCESS);
}