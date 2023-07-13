/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:05:00 by jubernar          #+#    #+#             */
/*   Updated: 2023/06/22 13:05:02 by jubernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdio.h"

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

int	ft_put_nbr(int nb)
{
	char	x;
	int		count;

	count = 0;
	if (nb == -2147483648)
		count = ft_put_str("-2147483648");
	else if (nb < 0)
	{
		count = ft_put_char('-');
		count = count + ft_put_nbr(-nb);
	}
	else if (nb >= 0 && nb <= 9)
	{
		x = nb + '0';
		count = ft_put_char(x);
	}
	else if (nb > 9)
	{
		count = count + ft_put_nbr(nb / 10);
		count = count + ft_put_nbr(nb % 10);
	}
	return (count);
}

int	main(void)
{
	char	str[20];

	scanf("%s", str);
	printf("\ntext = %s\n", str);
	return (0);
}
