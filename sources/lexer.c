/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_t_mini(t_minishell *t_mini)
{
	ft_printf("\ninput = %s\n", t_mini->input);
	ft_printf("pipe = %i\n", t_mini->pipe);
	ft_printf("in_redir = %i\n", t_mini->input_redirection);
	ft_printf("out_redir = %i\n", t_mini->output_redirection);
	ft_printf("nb_cmd = %i\n", t_mini->nb_cmd);
	//ft_printf("input = %s\n",t_mini->cmd_table);
	return (0);
}

int	add_lexer_table(t_lexer **root, char *str)
{
	t_lexer	*new_node;
	t_lexer	*curr;

	new_node = malloc(sizeof(t_lexer));
	new_node->next = NULL;
	new_node->content = str;
	if (*root == NULL)
	{
		*root = new_node;
		return (0);
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
	return (0);
}

int	yield_word(char *token, t_minishell *t_mini)
{
	int i;
	int len;
	char *str;
	
	len = 0;
	while (token[len]!= ' ' && token[len]!= 0)
	{
		len++;
	}
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = token[i];
		i++;
	}
	str[i] = '\0';
	add_lexer_table(&t_mini->lexer_table, str);
	return (i);
}

int	yield_quote(char *token, t_minishell *t_mini)
{
	int i;
	int len;
	char *str;

	i = 1;
	while (token[i]!= token[0] && token[i]!= 0)
	{
		i++;
	}
	len = i;
	if (token[i]== token[0])
		len++;
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = token[i];
		i++;
	}
	str[i] = '\0';
	add_lexer_table(&t_mini->lexer_table, str);
	return (i + 1); // + 1 is go beyond the closing quote
}

int	yield_var(char *token, t_minishell *t_mini)
{
	char *str;
	int i;
	int len;

	len = 0;
	while (token[len]!= ' ' && token[len]!= 0)
		len++;
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = token[i];
		i++;
	}
	str[i] = '\0';
	add_lexer_table(&t_mini->lexer_table, str);
	return (i);
}

int	yield_pipe(char *token, t_minishell *t_mini)
{
	char *str;

	t_mini->pipe += 1;
	str = malloc(sizeof (char) * (1 + 1));
	str[0] = token[0];
	str[1] = 0;
	add_lexer_table(&t_mini->lexer_table, str);
	return (1);
}

int	yield_redirection(char *redir, t_minishell *t_mini)
{
	char *str;

	if (redir[0] != redir[1])
	{
		str = malloc(sizeof (char) * (1 + 1));
		str[0] = redir[0];
		str[1] = 0;
		add_lexer_table(&t_mini->lexer_table, str);
		return (1);
	}
	if (redir[0] == redir[1])
	{
		str = malloc(sizeof (char) * (2 + 1));
		str[0] = redir[0];
		str[1] = redir[1];
		str[2] = 0;
		add_lexer_table(&t_mini->lexer_table, str);
		return (2);
	}
	return (0);
}

int	print_lst(t_lexer *lst)
{
	int i;

	i = 1;
	ft_printf("\n");
	while (lst != NULL)
	{
		printf("token %i = %s \n", i, lst->content);
		lst = lst->next;
		i++;
	}
	return (0);
}

int	lexer(t_minishell *t_mini)
{
	 // deal with " "
	 // deal with ''
	 // deal with |
	 // deal with < << >> >
	 // deal with strings
		 // deal with command
	 // deal with $
	char *input;
	int i;

	i = 0;
	input = t_mini->input;
	while (input[i] != 0)
	{
		if (input[i] == '<' || input[i] == '>')
			i += yield_redirection(&input[i], t_mini);  // done
		else if (ft_isalpha(input[i]) == 1 || input[i] == '-')
			i += yield_word(&input[i], t_mini); 		// WIP
		else if (input[i] == 39 || input[i] == 34)
			i += yield_quote(&input[i], t_mini);
	 	else if (input[i] == '$')
			i += yield_var(&input[i], t_mini);
		else if (input[i] == '|' )
			i += yield_pipe(&input[i], t_mini);
		else
			i++;
	}
	t_mini->nb_cmd = t_mini->pipe + 1;
	print_t_mini(t_mini);
	print_lst(t_mini->lexer_table);
	free(input);
	
	return (0);
}