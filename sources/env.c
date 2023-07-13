#include "minishell.h"

void	deallocate_env(t_list **root)
{
	t_list	*aux;
	t_list	*curr;

	curr = *root;
	while (curr != NULL)
	{
		aux = curr;
		free (aux->content);
		curr = curr->next;
		free (aux);
	}
	*root = NULL;
}

int	env_mini(t_minishell *mini, char **envp)
{
	int		i;
	t_list	*new;
	char	*new_var;

	i = 0;
	new_var = NULL;
	mini->env_mini = NULL;
	mini->main_pid = getpid();
	while (envp[i] != NULL)
	{
		new_var = ft_strdup(envp[i]);
		new = ft_lstnew((void *)new_var);
		if (!new)
		{
			deallocate_env(&mini->env_mini);
			return(EXIT_FAILURE);
		}
		ft_lstadd_back(&mini->env_mini, new);
		i++;
	}
	return(EXIT_SUCCESS);
}

int	env_builtin(t_minishell *mini)
{
	t_list *curr;

	curr= mini->env_mini;
	while (curr != NULL)
	{
		ft_putendl_fd(curr->content, 1);
		curr = curr->next;
	}
	return(EXIT_SUCCESS);
}