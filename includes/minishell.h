/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_lexer
{
	char			*content;
	struct s_lexer	*next;
}t_lexer;

typedef struct s_minishell
{
	char *input;  //prompt input
	t_lexer *lexer_table;
	char **cmd_table; // output du parser
	int pipe; // nb de pipe
	int input_redirection; // 1 si < 2 si <<
	int output_redirection; // 1 si > 2 si >>
	int nb_cmd; // nb de commande a executer
	char *limiter;
	char *in_file;
	char *out_file;
}t_minishell;

int	print_opening(void);

int	prompt(char **envp, t_minishell *t_mini);

// Lexer related functions
int	lexer(t_minishell *t_mini);

int	parser(t_minishell *t_mini);


//Utils
int		print_t_mini(t_minishell *t_mini);
int		print_lst(t_lexer *lst);
void	deallocate(t_lexer **head);
int		print_cmd_table(t_minishell *t_mini, int cmd);


// Path related functions
void    execute_command(char *input, char **envp);
char	*ft_access_path(char **cmd, int i);
char	**ft_access_list(char **cmd);
char	**ft_access_list_help(char *cmd_2, char **path_from_envp, int len, int i);
void	ft_free_tab(char **tab);
void	ft_free_exit(char *str1, char *str2, char **tab1, char **tab2);
int	ft_free(char *str1, char *str2, char **tab1, char **tab2);

#endif

