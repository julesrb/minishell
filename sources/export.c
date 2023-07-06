#include "minishell.h"

int size_env(char **envp)
{
    int i;

    i = 0;
    while(envp[i] != NULL)
        i++;
    return (i);
}

char	*ft_strrchr_set(const char *s, char *set)
{
	long	i;
    int j;
	char	*str;

	str = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
        j = 0;
        while (set[j] != '\0')
        {
            if (str[i] == (set[j] % 256))
                return (str + i);

            j++;
        }
        i--;
	}
	return (NULL);
}

int     check_arg_export(char *export_arg)
{
    char *var_name;
    int i;
    char *set = "$`\"'|><*?[]\\@#{}-+/^!()";

    i = 0;
    while(export_arg[i] != '=')
        i++;
    var_name = (char*)malloc(sizeof(var_name) * i + 1);
    ft_strlcpy(var_name, export_arg, i + 1);
    if (ft_isalpha(export_arg[0]) == 0)
        return (EXIT_FAILURE);
    else if (ft_strrchr_set(var_name, set) != NULL)
        return(ft_free(var_name, NULL, NULL, NULL));
    return (EXIT_SUCCESS);
}

int  check_update_var(char *cmd, t_list *env_mini)
{
    int i;
    t_list *curr;

    i = 0;
    curr = env_mini;
    while (cmd[i] != '=')
        i++;
    while (curr != NULL)
    {
        if (ft_strncmp(cmd, (char*)(curr->content), i) == EXIT_SUCCESS)
            return (EXIT_SUCCESS);
        curr = curr->next;
    }
    return (EXIT_FAILURE);
}

int     list_env_update(t_minishell *mini, char *var_update)
{
    t_list *curr;
    int i;
    char *new_var;

    i = 0;
    curr = mini->env_mini;
    while (var_update[i] != '=')
        i++;
    while (curr != NULL)
    {
        if (ft_strncmp(var_update, (char*)(curr->content), i) == EXIT_SUCCESS)
        {
            free(curr->content);
            new_var = ft_strdup(var_update);
            curr->content = (void*)new_var;
            return (EXIT_SUCCESS);
        }
        curr = curr->next;
    }
    return(EXIT_FAILURE);
}

char	*add_var_translation_export(t_minishell *mini, char *str)
{
	int i;
	char *translation;
	
	i = 0;
	translation = NULL;
	while (str[i] != 0 && str[i] != '$')
		i++;
	translation = var_translation(mini, &str[i]);
	str[i] = 0;
	i++;
	while (str[i] != 0 && str[i] != ' ')
		i++;
	translation = ft_strjoin(translation, &str[i]);
	translation = ft_strjoin(str, translation);
	return(translation);
}


char *adjust_var_env(t_minishell *mini, char *var_env, int count)
{
    char *adjust_var_env = NULL;
    char *temp_end = NULL;
    char *temp_trim = NULL;
    char *temp_start = NULL;

    while(var_env[count] != '=')
        count++;
    temp_start = (char*)malloc(sizeof(temp_start) * (count));
    ft_strlcpy(temp_start, var_env, count + 2);
    temp_end = ft_strdup(var_env + count + 1);
    if (ft_strchr(var_env, '\"') != NULL)
    {
        temp_trim = ft_strtrim(temp_end, (const char*)"\"");
        if (ft_strrchr(temp_trim, '$') > 0)
            adjust_var_env = ft_strjoin(temp_start, add_var_translation_export(mini, temp_trim));
        else
        {
            adjust_var_env = ft_strjoin(temp_start, temp_trim);
            free(temp_trim);
        }
    }
    else if (ft_strchr(var_env, '\'') != NULL)
    {
        temp_trim = ft_strtrim(temp_end, (const char*)"\'");
        adjust_var_env = ft_strjoin(temp_start, temp_trim);
        free(temp_trim);
    }
    else
    {
        free(temp_start);
        adjust_var_env = ft_strdup(var_env);
    }
    free(temp_end);
    return (adjust_var_env);
}

int     export_builtin(char **cmd, t_minishell *mini)
{
    t_list *new;
    t_list *curr;
    char *new_var= NULL;
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
        exit(EXIT_SUCCESS);
    }
    i = 1;
    while(cmd[i] && (check_arg_export(cmd[i]) == EXIT_SUCCESS))
    {
        if (check_update_var(cmd[i], mini->env_mini) == EXIT_SUCCESS)
        {
            new_var = adjust_var_env(mini, cmd[i], 0);
            if(list_env_update(mini, new_var) == EXIT_FAILURE)
            {
                deallocate_env(&mini->env_mini);
                return(EXIT_FAILURE);
            }
        }
        else
        {
            new_var = adjust_var_env(mini, cmd[i], 0);
            new = ft_lstnew((void*)ft_strdup(new_var));
            if (!new)
            {
                deallocate_env(&mini->env_mini);
                return(EXIT_FAILURE);
            }
            ft_lstadd_back(&mini->env_mini, new);
        }
        i++;
        free(new_var);
    }
    return(EXIT_SUCCESS);
}