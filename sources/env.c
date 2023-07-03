#include "minishell.h"

int     env_mini(t_minishell *mini, char **envp)
{
    int  i;

    i = 0;
    while(envp[i])
        i++;
    mini->env_mini = (char **)malloc(sizeof(mini->env_mini) * i++);
    if (!mini->env_mini)
        return(EXIT_FAILURE);
    i = 0;
    while (envp[i] != NULL)
    {
        mini->env_mini[i] = ft_strdup(envp[i]);
        if (!mini->env_mini[i])
        {
            ft_free_tab(mini->env_mini);
            return(EXIT_FAILURE);
        }
        i++;
    }
    mini->env_mini[i] = NULL;
    return(EXIT_SUCCESS);
}

int     env_builtin(t_minishell *mini)
{
    int i;

    i = 0;
    while (mini->env_mini[i] != NULL)
    {
        ft_putendl_fd(mini->env_mini[i], 1);
        i++;
    }
    return(EXIT_SUCCESS);
}