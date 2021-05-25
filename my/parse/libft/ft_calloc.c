/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:08:37 by whan              #+#    #+#             */
/*   Updated: 2020/11/02 17:30:48 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*pt;
	unsigned char	null;
	size_t			i;
	unsigned char	*upt;

	null = 0;
	pt = (void*)malloc(size * count);
	i = 0;
	upt = (unsigned char *)pt;
	if (!pt)
		return (NULL);
	while (i < count * size)
	{
		upt[i] = null;
		i++;
	}
	return (pt);
}
