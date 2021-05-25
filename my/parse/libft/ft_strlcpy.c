/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:41:21 by whan              #+#    #+#             */
/*   Updated: 2020/10/22 10:46:48 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t len;

	len = 0;
	if (!src || !dst)
		return (len);
	if (n > 0)
	{
		while (src[len] && len < n - 1)
		{
			dst[len] = src[len];
			len++;
		}
		dst[len] = 0;
	}
	while (src[len])
		len++;
	return (len);
}
