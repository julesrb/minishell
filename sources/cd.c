#include "minishell.h"

int     update_env_pwd(t_minishell *mini, char *var_env)
{
    t_list *curr;
    char *new_var_env;
    char *temp1 = NULL;
    char *temp2 = NULL;
    char *temp3 = NULL;

    curr = mini->env_mini;
    while (curr != NULL)
    {
        if (ft_strncmp(var_env, (char*)(curr->content), ft_strlen(var_env)) == EXIT_SUCCESS)
        {
            free(curr->content);
            temp1 = ft_strdup(var_env);
            temp2 = ft_strjoin(temp1, (char*)"=");
            temp3 = ft_strdup(getenv(var_env));
            new_var_env = ft_strjoin(temp2, temp3);
            printf("%s: %s\n", var_env, new_var_env);
            free(temp3);
            curr->content = (void*)new_var_env;
            return (EXIT_SUCCESS);
        }
        curr = curr->next;
    }
    return(EXIT_FAILURE);
}

int     cd_builtin(char *cmd, t_minishell *mini)
{
    int result;

    (void)mini;
    result = chdir(cmd);
    if (result == -1)
    {
        ft_putstr_fd("cd: ", 2);
        perror(cmd);
        return(EXIT_FAILURE);
    }
    update_env_pwd(mini, "PWD");
    update_env_pwd(mini, "OLDPWD"); 
    return (EXIT_SUCCESS);
}