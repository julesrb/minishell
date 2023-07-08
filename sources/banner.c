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
    printf("╔════════════════════════════════════╗\n");
    printf("║        WELCOME TO MINISHELL        ║\n");
    printf("╚════════════════════════════════════╝\n");
	return (EXIT_SUCCESS);
}

int	print_exit(void)
{
    printf("╔════════════════════════════════════╗\n");
    printf("║  THANK YOU FOR CHOOSING MINISHELL, ║\n");
	printf("║           SEE YOU SOON!            ║\n");
    printf("╚════════════════════════════════════╝\n");
	return (EXIT_SUCCESS);
}