/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 20:35:33 by whan              #+#    #+#             */
/*   Updated: 2020/10/22 16:39:59 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sum;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return ((void *)0);
	sum = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!sum)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		sum[j] = s1[i++];
		j++;
	}
	i = 0;
	while (s2[i])
	{
		sum[j++] = s2[i];
		i++;
	}
	sum[j] = 0;
	return (sum);
}
