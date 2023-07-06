#include "minishell.h"


int	exit_builtin(char **cmd, t_minishell *mini)
{
	int	i;

	i = 0;
	(void)mini;
	while (cmd[i] != NULL)
		i++;
	if (i > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": too many arguments", 2);
		return (0);
	}
	free_mini(mini);
	//kill(mini->pid_mini, SIGTERM);
	exit (1);
	return (0);
}