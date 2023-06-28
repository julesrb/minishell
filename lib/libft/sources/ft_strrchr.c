/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:16:11 by gbussier          #+#    #+#             */
/*   Updated: 2023/01/05 08:47:06 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c);

int	main(void)
{
	char str[] = "bonjour";
	int c;

	c = 'b';
	printf ("%s\n", strrchr(str, c));
	printf ("%s\n", ft_strrchr(str, c));
}
*/

char	*ft_strrchr(const char *s, int c)
{
	long	i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (str[i] == (c % 256))
			return (str + i);
		i--;
	}
	return (NULL);
}
