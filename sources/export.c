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
        if (strncmp(cmd, (char*)(curr->content), i) == EXIT_SUCCESS)
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
    while(cmd[i] && (check_arg_export(cmd[i]) == EXIT_SUCCESS))
    {
        if (check_update_var(cmd[i], mini->env_mini) == EXIT_SUCCESS)
        {
            if(list_env_update(mini, cmd[i]) == EXIT_FAILURE)
            {
                deallocate_env(&mini->env_mini);
                return(EXIT_FAILURE);
            }
        }
        else
        {
            new = ft_lstnew((void*)ft_strdup(cmd[i]));
            if (!new)
            {
                deallocate_env(&mini->env_mini);
                return(EXIT_FAILURE);
            }
            ft_lstadd_back(&mini->env_mini, new);
        }
        i++;
    }
    return(EXIT_SUCCESS);
}