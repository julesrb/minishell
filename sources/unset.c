#include "minishell.h"

int  check_unset_var(char *cmd, t_list *env_mini)
{
    while (env_mini != NULL)
    {
        if (ft_strncmp(cmd, (char *)(env_mini->content), strlen(cmd)) == 0)
            return (EXIT_SUCCESS);
        env_mini = env_mini->next;
    }
    return (EXIT_FAILURE);
}

int     lst_env_remove(t_minishell *mini, char *var_unset)
{
    t_list *prev;
    t_list *curr;

    prev = NULL;
    curr = mini->env_mini;
    while (curr != NULL)
    {
        if (ft_strncmp(var_unset, (char *)(curr->content), ft_strlen(var_unset)) == 0)
        {
            if (prev == NULL)
                mini->env_mini = curr->next;
            else
                prev->next = curr->next;
            free(curr->content);
            free(curr);
            return (EXIT_SUCCESS);
        }
        prev = curr;
        curr = curr->next;
    }
    return EXIT_FAILURE;
}

int     unset_builtin(char **cmd, t_minishell *mini)
{
    int i;

    i = 1;
    while (cmd[i] != NULL)
    {
        if (check_unset_var(cmd[i], mini->env_mini) == EXIT_SUCCESS)
            lst_env_remove(mini, cmd[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}