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
# include "get_next_line.h"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_minishell
{
	char **cmd_table; // output du parser
	int pipe; // nb de pipe			path = ft_access_path(cmd_split, 0);
			if (!path)
			{   
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd_split[0], 2);
				ft_putendl_fd(": command not found", 2);
				exit(ft_free(path, NULL, cmd_split, NULL));
			}
			if(execve(path, cmd_split, envp) == -1)
			{   
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd_split[0], 2);
				ft_putendl_fd(": command not found", 2);
				exit(ft_free(path, NULL, cmd_split, NULL));
			}

int	print_opening(void);
char *prompt(char **envp);

// Path related functions
void    executor(t_minishell mini, char **envp);
char	*ft_access_path(char **cmd, int i);
char	**ft_access_list(char **cmd);
char	**ft_access_list_help(char *cmd_2, char **path_from_envp, int len, int i);
void	ft_free_tab(char **tab);
void	ft_free_exit(char *str1, char *str2, char **tab1, char **tab2);
int	ft_free(char *str1, char *str2, char **tab1, char **tab2);
void	exec(char *cmd, char **envp);

int     output_redirection(t_minishell mini);
int     input_redirection(t_minishell mini);
void	here_doc(char *limiter);
#endif

