#include "minishell.h"

int size_env(char **envp)
{
    int i;

    i = 0;
    while(envp[i] != NULL)
        i++;
    return (i);
}

int     check_arg_export(char *export_arg)
{
    if (export_arg[0] == '=')
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

/* int  check_update_var(char *cmd, t_list *env_mini)
{
    while (env_mini != NULL)
    {
        if (strncmp(cmd[i]))
        env_mini = env_mini->next;
    }
    return (EXIT_SUCCESS);
} */

int     export_builtin(char **cmd, t_minishell *mini)
{
    t_list *new;
    t_list *curr;
    int i;

    curr = mini->env_mini;
    i = 0;
    while (cmd[i] != NULL)
        i++;
    if (i == 1)
    {
        while (curr)
        {
            printf("declare -x %s\n", (char*)(curr->content));
            curr = curr->next;
        }
    }
    i = 1;
    while(cmd[i] && check_arg_export(cmd[i]) == EXIT_SUCCESS)
    {
/*         if (check_update_var(cmd[i], mini->env_mini) == EXIT_SUCCESS)
        {
            ft_list_update(cmd[i]);
        }
        else */
        new = ft_lstnew((void*)cmd[i]);
        if (!new)
        {
            deallocate_env(&mini->env_mini);
            return(EXIT_FAILURE);
        }
        //printf("new: %s\n", (char*)new->content);
        ft_lstadd_back(&mini->env_mini, new);
        i++;
    }
    return(EXIT_SUCCESS);
}