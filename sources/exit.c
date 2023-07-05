#include "minishell.h"

int	exit_builtin(char **cmd, t_minishell *mini)
{
	int	i;

	i = 0;
	ft_putendl_fd("EXIT",1);
	while (cmd[i] != NULL)
		i++;
	if (i > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": too many arguments", 2);
	}
	free_mini(mini);
	ft_putendl_fd("EXIT",1);
	exit (1);
	return (0);
}