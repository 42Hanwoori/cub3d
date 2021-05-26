/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:50:43 by whan              #+#    #+#             */
/*   Updated: 2020/10/20 15:24:49 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	f;

	f = (unsigned char)c;
	while (n--)
	{
		if (*(unsigned char *)s == f)
			return ((void *)s);
		s++;
	}
	return ((void *)0);
}
