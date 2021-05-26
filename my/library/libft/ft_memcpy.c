/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:12:23 by whan              #+#    #+#             */
/*   Updated: 2020/10/22 15:03:05 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			a;
	unsigned char	*udst;
	unsigned char	*usrc;

	a = 0;
	if (!dst && !src)
		return (0);
	udst = (unsigned char *)dst;
	usrc = (unsigned char *)src;
	while (a < n)
	{
		udst[a] = usrc[a];
		a++;
	}
	return (dst);
}
