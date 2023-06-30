/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	ft_put_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_put_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_put_str("(null)"));
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	main(int argc, char **argv)
{

	if (argc == 4)
	{
		ft_put_str("arg 1 = ");
		ft_put_str(argv[1]);
		ft_put_str("\n");
		ft_put_str("arg 2 = ");
		ft_put_str(argv[2]);
		ft_put_str("\n");
		ft_put_str("arg 3 = ");
		ft_put_str(argv[3]);
		ft_put_str("\n");
	}
	else
	{
		ft_put_str("arg error\n");
		return (1);
	}
	return (0);
}


