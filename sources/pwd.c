#include "minishell.h"

int    pwd_builtin(t_minishell *mini)
{
    t_list *curr;

    curr = mini->env_mini;

    while (ft_strncmp(curr->content, "PWD=", 4) != 0)
    {
        curr = curr->next;
    }
    ft_putendl_fd(curr->content + 4, 1);
    return(EXIT_SUCCESS);
}