/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:57:26 by whan              #+#    #+#             */
/*   Updated: 2020/11/02 16:14:14 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			a;
	unsigned char	sub;
	unsigned char	*usen;

	a = 0;
	sub = (unsigned char)c;
	usen = (unsigned char*)b;
	while (a++ < len)
		*usen++ = sub;
	return (b);
}
