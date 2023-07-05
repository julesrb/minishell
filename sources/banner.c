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
