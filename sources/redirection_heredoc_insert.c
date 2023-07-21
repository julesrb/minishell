/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <gbussier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:03 by gbussier          #+#    #+#             */
/*   Updated: 2023/07/18 15:53:05 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_put_in_insert(char *limiter)
{
	char	*heredoc_line;

	while (1)
	{
		heredoc_line = readline("heredoc> ");
		if (ft_strncmp(heredoc_line, limiter, ft_strlen(limiter)) == 0)
		{
			free(heredoc_line);
			exit(EXIT_SUCCESS);
		}
	}
}
