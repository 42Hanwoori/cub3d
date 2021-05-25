/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:13:19 by whan              #+#    #+#             */
/*   Updated: 2020/10/23 12:05:44 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*udst;
	unsigned char	*usrc;

	i = 0;
	udst = (unsigned char *)dst;
	usrc = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (dst <= src)
		while (i < len)
		{
			udst[i] = usrc[i];
			i++;
		}
	else
		while (len > 0)
		{
			udst[i + len - 1] = usrc[i + len - 1];
			len--;
		}
	return (dst);
}
