#include "minishell.h"

int     export_builtin(char **cmd, char **envp)
{
    int i;

    i = 0;
    while(cmd[i] != NULL)
        i++;
    if (i == 1)
    {
        i = 0;
        while (envp[i] != NULL)
        {
            printf("declare -x %s\n", envp[i]);
            i++;
        }
    }
    return(EXIT_SUCCESS);
}