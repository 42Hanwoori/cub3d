/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:00:09 by whan              #+#    #+#             */
/*   Updated: 2020/11/02 17:37:31 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	how_long(const char *sen)
{
	size_t len;

	len = 0;
	while (sen[len])
		len++;
	return (len);
}

char			*ft_strnstr(const char *haystack,
	const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && needle[j] && i + j < len)
				j++;
			if (j == how_long(needle))
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
