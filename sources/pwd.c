#include "minishell.h"

int    pwd_builtin(void)
{
    char *pwd;

    pwd = getenv("PWD");
    if (!pwd)
        return(EXIT_FAILURE);
    ft_putendl_fd(pwd, 1);
    return(EXIT_SUCCESS);
}