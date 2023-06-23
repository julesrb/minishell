/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_opening(void)
{
	ft_printf("/ ******************************************************* /\n");
	ft_printf("/                                                         /\n");
	ft_printf("/   oo oo   o  o   o  o   oooo  o   o  ooooo  o     o     /\n");
	ft_printf("/  o  o  o  |  oo  o  |  o      o   o  o      o     o     /\n");
	ft_printf("/  o  o  o  |  o o o  |   ooo   ooooo  ooooo  o     o     /\n");
	ft_printf("/  o  o  o  |  o  oo  |      o  o   o  o      o     o     /\n");
	ft_printf("/  o  o  o  |  o   o  |  oooo   o   o  ooooo  oooo  oooo  /\n");
	ft_printf("/                                                         /\n");
	ft_printf("/ ******************************************************* /\n");
	return (EXIT_SUCCESS);
}

/* int	print_opening(void)
{
	int		fd;
	char	*line;

	fd = open("./sources/banner.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("opening_failed");
		return (0);
	}
	ft_printf("opening_ok");
	line = get_next_line(fd);
	while (!line)
	{
		line = get_next_line(fd);
		ft_printf("%s", line);
	}
	return (EXIT_SUCCESS);
} */