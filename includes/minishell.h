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
# include <termcap.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_llist
{
	char			*content;
	struct s_llist	*next;
}t_llist;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}t_redir;

typedef struct s_minishell
{
	char	*input;
	char	***cmd_table;
	t_list	*env_mini;
	t_llist	*lexer_table;
	t_redir *redir_in;
	t_redir *redir_out;
	int		pipe;
	int		error_redir;
	int		error_pipe;
	int		nb_cmd;
	int		exit_status;
	int		main_pid;
	char	**envp;
}t_minishell;

extern t_minishell	*mini_global;

int		print_opening(void);
int		print_exit(void);
int		print_exit(void);

int		prompt(t_minishell *mini);

// Lexer related functions
int		lexer(t_minishell *mini);
int		add_to_list(t_llist **root, char *str);

int		parser(t_minishell *mini);

void	arg_check(int argc, char **argv);

char	*add_var_translation(t_minishell *mini, char *str);
char	*var_translation(t_minishell *mini, char *var);
int		quote_translation(t_minishell *mini, t_llist *curr);

// Utils
void	deallocate_list(t_llist **head);
void	free_mini(t_minishell *mini);
int		lst_size(t_llist *lst);
int		add_to_redir(t_redir **root, int type, char *str);

// Debug
int		print_t_mini(t_minishell *mini);
int		print_lst(t_llist *lst);
int		print_cmd_table(t_minishell *mini, int cmd);
int		print_cmd(char **cmd_line);

// Token
int		token_yield_redir(char *redir, t_minishell *mini);
int		token_yield_quote(char *token, t_minishell *mini);
int		token_yield_pipe(char *token, t_minishell *mini);
int		token_yield_word(char *token, t_minishell *mini);
int		token_yield_var(char *token, t_minishell *mini);

// Path related functions
char	*ft_access_path(char **cmd, int i, t_minishell *mini);
char	**ft_access_list(char **cmd, t_minishell *mini);
char	**ft_access_list_help(char *cmd_2, char **path_from_envp, int len, int i);
void	ft_free_tab(char **tab);
void	ft_free_exit(char *str1, char *str2, char **tab1, char **tab2);
int		ft_free(char *str1, char *str2, char **tab1, char **tab2);
char *find_executable(char **cmd, t_minishell *mini);
int is_absolute_path(char *path);
int is_relative_path(char *path);
char    *ft_relative_path(char *cmd, t_minishell *mini);
char   *origine_path(int count_trim, t_minishell *mini);
char *getenv_mini(char *env_mini, t_minishell *mini);
int     ft_count_trim(char *cmd);
int     ft_count_trim(char *cmd);

// Builtin functions
int    pwd_builtin(t_minishell *mini);
int		env_mini(t_minishell *mini, char **envp);
int		env_builtin(t_minishell *mini);
int		echo_builtin(char **cmd_split);
int		export_builtin(char **cmd, t_minishell *mini);
int		unset_builtin(char **cmd, t_minishell *mini);
int		exit_builtin(char **cmd, t_minishell *mini);
int     cd_builtin(char *cmd, t_minishell *mini);

int		input_redirection(t_minishell mini);
int		output_redirection(t_minishell mini);
int	outfile_insert(t_minishell mini);
int	infile_insert(t_minishell mini);
void	here_doc(char *limiter);

//environment function
void	deallocate_env(t_list **root);
int     list_env_update(t_minishell *mini, char *var_update);

// signal
void signal_main(t_minishell *mini);
void signal_child(t_minishell *mini, struct sigaction *sa);

// execute_utils.c
int max_length(const char* str1, const char* str2);
int	is_builtin(char *cmd);
int	is_env_function(char *cmd);

// execute_process.c
int     child_process(t_minishell *mini, int index, char **cmd, int **fd);
int	create_process_fd(char **cmd, t_minishell *mini, int index, int **fd);
int		**create_pipe(t_minishell *mini);
int     close_fd(int **fd);

//execute.c
int		execute_builtin(char **cmd_split, t_minishell *mini);
int	exec(char **cmd, char **envp, t_minishell *mini);
int  execute_single_command(t_minishell *mini);
int		execute_several_commands(t_minishell *mini);
int    executor(t_minishell *mini);

#endif

