/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(void)
{
	char *input;
	int	history;

	history = open("history.txt", O_CREAT | O_TRUNC, 999);
	if (history == -1)
		return(0);
	input = readline("[Minishell] >");
	int rt = write(history, input, ft_strlen(input));
	ft_printf("write return = %i\n", rt);
	//add_history(input);
	close(history);
	free(input);
	return (0);
}

int main(void)
{

	print_opening();
	while(1)
	{
		prompt();
	}

	return(0);
}

