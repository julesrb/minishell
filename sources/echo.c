#include "minishell.h"

int     echo_builtin(char **cmd_split)
{
	int i;

	i = 1;
	while (cmd_split[i] != NULL)
	{
		ft_put_str(cmd_split[i]);
		i++;
	}
	ft_put_str("\n");
	return (1);
}
