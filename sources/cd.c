#include "minishell.h"


char    *ft_relative_path_cd(char *cmd, t_minishell *mini)
{
    char *relative_path = NULL;
    char *path_trim = NULL;
    char *path_trim2 = NULL;
    char *env_path = NULL;
    char *path_root= NULL;
    char *path_root2= NULL;
    int count_trim;

    count_trim = 0;
    if (ft_strncmp(cmd, "./", 2) == 0)
    {
        path_trim = ft_strtrim(cmd, "./");
        path_trim2 = ft_strtrim(path_trim, (char*)"/");
        env_path = ft_strdup(getenv_mini("PWD", mini));
        path_root = ft_strjoin(env_path, (char*)"/");
        path_root2 = ft_strjoin(path_root, path_trim2);
        relative_path = ft_strtrim(path_root2, (char*)"/");
    }
    else if (ft_strncmp(cmd, "../", 3) == 0)
    {
        path_trim = ft_strtrim(cmd, "../");
        path_trim2 = ft_strtrim(path_trim, (char*)"/");
        count_trim = ft_count_trim(cmd);
        env_path = origine_path(count_trim, mini);
        path_root = ft_strjoin(env_path, (char*)"/");
        path_root2 = ft_strjoin(path_root, path_trim2);
        relative_path = ft_strtrim(path_root2, (char*)"/");
    }
    else if (ft_isalnum(cmd[0]) != 0)
    {
        path_trim = ft_strtrim(cmd, (char*)"/");
        env_path = origine_path(0, mini);
        if (ft_strlen(getenv_mini("PWD", mini)) == 1)
            relative_path = ft_strjoin(env_path, path_trim);
        else
        {
            path_root = ft_strjoin(env_path, (char*)"/");
            relative_path = ft_strjoin(path_root, path_trim);
        }
    }
    else if ((ft_strncmp(cmd, "..", 2) == 0) && ft_strlen(cmd) == 2)
    {
        path_trim = ft_strtrim(cmd, "..");
        count_trim = 1;
        relative_path = origine_path(count_trim, mini);
    }
    else if ((cmd[0] == '.') && (ft_strlen(cmd) == 1))
    {
        relative_path = ft_strdup(getenv_mini("PWD", mini));
    }
    else if ((cmd[0] == '-' && ft_strlen(cmd) == 1))
    {
        relative_path = ft_strdup(getenv_mini("OLDPWD", mini));
    }
    else if ((cmd[0] == '~' && ft_strlen(cmd) == 1))
    {
        relative_path = ft_strdup((char*)"/");
    }
    return(relative_path);
}

char *convert_path_to_absolute(char *cmd, t_minishell *mini)
{
    char *result;

    if (is_absolute_path(cmd) == EXIT_SUCCESS)
    {
        if ((cmd[ft_strlen(cmd) - 1] == '/') && (ft_strlen(cmd) > 1))
        {
            result = ft_strdup(cmd);
            ft_bzero((void*)(result + ft_strlen(cmd) - 1), 1);
        }
        else
            result = ft_strdup(cmd);
        return(result);
    }
    else if ((is_relative_path(cmd) == EXIT_SUCCESS) || ((ft_strlen(cmd) == 1) && (cmd[0] == '-')))
    {
        result = ft_relative_path_cd(cmd, mini);
        return(result);
    }
    else if (ft_isalnum(cmd[0]) != 0)
    {
        result = ft_relative_path_cd(cmd, mini);
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
/*             printf("%s: %s\n", env_mini_to_update, new_var_env); */
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
    oldpwd = ft_strdup(getenv_mini("PWD", mini));
    if(update_env_mini(mini,"OLDPWD", oldpwd) == EXIT_FAILURE)
        return(EXIT_FAILURE);
    if(update_env_mini(mini,"PWD", pwd) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return(EXIT_SUCCESS);
}

int     cd_builtin(char *cmd, t_minishell *mini)
{
    int result;
    char *cmd_replace = NULL;

    if ((ft_strlen(cmd) == 1) && (cmd[0] == '-'))
    {
        cmd_replace = ft_strdup(getenv_mini("OLDPWD", mini));
        result = chdir(cmd_replace);
        free(cmd_replace);
    }
    else if ((cmd[0] == '~') && (ft_strlen(cmd) == 1))
    {
        cmd_replace = ft_strdup(getenv_mini("HOME", mini));
        result = chdir(cmd_replace);
        free(cmd_replace);
    }
    else
        result = chdir(cmd);
    if (result == -1)
    {
        printf("testerror\n");
        ft_putstr_fd("cd: ", 2);
        perror(cmd);
        return(EXIT_FAILURE);
    }
    update_env_cd(mini, cmd);
    return (EXIT_SUCCESS);
}