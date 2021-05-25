/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:48:42 by whan              #+#    #+#             */
/*   Updated: 2020/10/22 09:40:49 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t d_len;
	size_t s_len;

	j = 0;
	i = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (dstsize < d_len)
		return (s_len + dstsize);
	while (dst[i])
		i++;
	if (d_len < dstsize - 1 && dstsize > 0)
	{
		while (dstsize - i - 1 > 0 && src[j])
			dst[i++] = src[j++];
	}
	dst[i] = 0;
	return (s_len + d_len);
}
