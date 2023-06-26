/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbussier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:16:15 by gbussier          #+#    #+#             */
/*   Updated: 2022/12/16 19:09:04 by gbussier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
/*
#include <string.h>
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set);
int		checkchar(const char c, char const *set);

int	main(void)
{
	char const	s1[] = "  \t \t \n   \n\n\t";
	char const	s2[] = "";
	char const	set[] = " \n\t";

	printf ("%s%s\n", "result test 1: ", ft_strtrim(s1, set));
	printf ("%s%s\n", "result test 2: ", ft_strtrim(s2, set));
}
*/

int	checkchar(const char c, char const *set)
{
	size_t	sizeset;
	size_t	i;

	i = 0;
	sizeset = ft_strlen(set);
	while (i < sizeset)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	end;
	size_t	i;
	size_t	start;
	size_t	size;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (checkchar(s1[start], set))
		start++;
	while (checkchar(s1[end - 1], set))
		end--;
	size = end - start + 1;
	if (end <= start)
		size = 1;
	strtrim = (char *)malloc(sizeof(*strtrim) * size);
	if (!strtrim)
		return (NULL);
	while (start != end && start <= end)
		strtrim[i++] = s1[start++];
	strtrim[i] = '\0';
	return (strtrim);
}
