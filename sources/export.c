#include "minishell.h"

int size_env(char **envp)
{
    int i;

    i = 0;
    while(envp[i] != NULL)
        i++;
    return (i);
}

int     export_builtin(char **cmd, t_minishell mini)
{
    int i;
    int j;
    int k;
    char **new_var;

    i = 0;
    while(cmd[i] != NULL)
        i++;
    if (i == 1)
    {
        j = 0;
        while (mini.env_mini[j] != NULL)
        {
            printf("declare -x %s\n", mini.env_mini[j]);
            j++;
        }
        return (EXIT_SUCCESS);
    }
    new_var = (char **)malloc(sizeof(new_var) * i);
    i = 0;
    while (cmd[i + 1] != NULL)
    {
        new_var[i] = ft_strdup(cmd[i + 1]);
        if (!new_var[i])
        {
            ft_free_tab(new_var);
            return(EXIT_FAILURE);
        }
        i++;
    }
    new_var[i] = NULL;
    k = 0;
    while (new_var[k] != NULL)
    {
        mini.env_mini[size_env(mini.env_mini) + k] = new_var[k];
        k++;
    }
    return(EXIT_SUCCESS);
}