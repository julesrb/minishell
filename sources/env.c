#include "minishell.h"

void	deallocate_env(t_list **root)
{
	t_list	*aux;
	t_list	*curr;

	curr = *root;
	while (curr != NULL)
	{
		aux = curr;
		curr = curr->next;
		free (aux->content);
		free (aux);
	}
	*root = NULL;
}

int     env_mini(t_minishell *mini, char **envp)
{
	int	i;
	t_list *new;
	char *new_var = NULL;

	i = 0;
	mini->env_mini = NULL;
	mini->main_pid = getpid();
	while (envp[i] != NULL)
	{
		new_var= ft_strdup(envp[i]);
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

int     env_builtin(t_minishell *mini)
{
	int i;

	i = 0;
	while (mini->env_mini)
	{
		ft_putendl_fd(mini->env_mini->content, 1);
		mini->env_mini = mini->env_mini->next;
	}
	exit (EXIT_SUCCESS);
}