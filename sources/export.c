#include "minishell.h"

int size_env(char **envp)
{
    int i;

    i = 0;
    while(envp[i] != NULL)
        i++;
    return (i);
}

int    env_mini_export(t_minishell *mini, char **export)
{
    int  i;
    int j;
    char **new_env;

    i = 0;
    j = 0;
    while(mini->env_mini[i])
        i++;
    while(export[j])
        j++;
    new_env = (char **)malloc(sizeof(new_env) * (i + j + 1));
    if (!new_env)
        return(EXIT_FAILURE);
    i = 0;
    while (mini->env_mini[i] != NULL)
    {
        new_env[i] = ft_strdup(mini->env_mini[i]);
        if (!new_env[i])
        {
            ft_free_tab(new_env);
            return(EXIT_FAILURE);
        }
        i++;
    }
    j = 0;
    while (export[j] != NULL)
    {
        new_env[i + j] = ft_strdup(export[j]);
        if (!new_env[i + j])
        {
            ft_free_tab(new_env);
            return(EXIT_FAILURE);
        }
        j++;
    }
    new_env[i + j] = NULL;
    ft_free_tab(mini->env_mini);
    ft_free_tab(export);
    mini->env_mini = new_env;
    return(EXIT_SUCCESS);
}

int     export_builtin(char **cmd, t_minishell *mini)
{
    int i;
    int j;
    char **new_var;

    i = 0;
    while(cmd[i] != NULL)
        i++;
    if (i == 1)
    {
        j = 0;
        while (mini->env_mini[j] != NULL)
        {
            ft_putstr_fd("declare -x ", 1);
            ft_putendl_fd(mini->env_mini[j], 1);
            j++;
        }
        exit (EXIT_SUCCESS);
    }
    new_var = (char **)malloc(sizeof(new_var) * i);
    if (!new_var)
        return (EXIT_FAILURE);
    j = 0;
    while (cmd[j + 1] != NULL)
    {
        new_var[j] = ft_strdup(cmd[j + 1]);
        if (!new_var[j])
        {
            ft_free_tab(new_var);
            exit(EXIT_FAILURE);
        }
        j++;
    }
    new_var[j] = NULL;
    env_mini_export(mini, new_var);
    return(EXIT_SUCCESS);
}