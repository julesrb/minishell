#include "minishell.h"

int    pwd_builtin(void)
{
    char *pwd;

    pwd = getenv("PWD");
    if (!pwd)
        return(EXIT_FAILURE);
    printf("%s\n", pwd);
    return(EXIT_SUCESS);
}