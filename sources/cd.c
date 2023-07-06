#include "minishell.h"

char *convert_path_to_absolute(char *cmd, t_minishell *mini)
{
    char *result;

    if (is_absolute_path(cmd) == EXIT_SUCCESS)
        return(cmd);
    else if (is_relative_path(cmd) == EXIT_SUCCESS)
    {
        result = ft_relative_path(cmd, mini);
        return(result);
    }
    return (NULL);
}

int     update_env_mini(t_minishell *mini, char *env_mini_to_update, char *new_value)
{
    t_list *curr;
    char *new_var_env = NULL;
    char *temp1 = NULL;
    char *temp2 = NULL;
    char *temp3 = NULL;

    curr = mini->env_mini;
    while (curr != NULL)
    {
        if (ft_strncmp(env_mini_to_update, (char*)(curr->content), ft_strlen(env_mini_to_update)) == EXIT_SUCCESS)
        {
            free(curr->content);
            temp1 = ft_strdup(env_mini_to_update);
            temp2 = ft_strjoin(temp1, (char*)"=");
            temp3 = ft_strdup(new_value);
            new_var_env = ft_strjoin(temp2, temp3);
            printf("%s: %s\n", env_mini_to_update, new_var_env);
            free(temp3);
            curr->content = (void*)new_var_env;
            return (EXIT_SUCCESS);
        }
        curr = curr->next;
    }
    return(EXIT_FAILURE);
}


int     update_env_cd(t_minishell *mini, char *cd)
{
    char *oldpwd = NULL;
    char *pwd = NULL;

    pwd = convert_path_to_absolute(cd, mini);
    printf("new pwd apres update %s\n", pwd);
    oldpwd = ft_strdup(getenv_mini("PWD", mini));
    printf("old pwd apres update %s\n", oldpwd);
    if(update_env_mini(mini,"OLDPWD", oldpwd) == EXIT_FAILURE)
        return(EXIT_FAILURE);
    if(update_env_mini(mini,"PWD", pwd) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return(EXIT_SUCCESS);
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
    update_env_cd(mini, cmd);
    return (EXIT_SUCCESS);
}