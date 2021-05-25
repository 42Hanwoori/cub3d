/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:46:35 by whan              #+#    #+#             */
/*   Updated: 2020/10/21 14:54:52 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*udst;
	unsigned char	*usrc;
	unsigned char	check;

	i = 0;
	udst = (unsigned char *)dst;
	usrc = (unsigned char *)src;
	check = (unsigned char)c;
	if (!dst && !src)
		return ((void *)0);
	while (i < n)
	{
		udst[i] = usrc[i];
		if (usrc[i] == check)
			return (&dst[i + 1]);
		i++;
	}
	return ((void *)0);
}
