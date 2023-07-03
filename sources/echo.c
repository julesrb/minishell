#include "minishell.h"

int     echo_builtin(char **cmd_split)
{
	int i;
	int n;

	i = 1;
	n = 1;
	ft_put_str("*");
	if (ft_strncmp(cmd_split[i], "-n", 2) == EXIT_SUCCESS)
	{
		n = 0;
		i++;
	}
	while (cmd_split[i] != NULL)
	{
		ft_put_str(cmd_split[i]);
		i++;
	}
	if (n == 1)
		ft_put_str("\n");
	return (1);
}
