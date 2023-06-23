#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;

    while(1)
    {
        input = readline("[Minishell] >");
        add_history(input);
    }
    free(input);
    return(0);
}