/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 11:29:25 by whan              #+#    #+#             */
/*   Updated: 2020/11/02 17:32:11 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*int_to_char(char *s, int n, int len)
{
	int	i;

	s[len] = 0;
	if (n == -2147483648)
	{
		s[0] = '-';
		s[1] = '2';
		return (int_to_char(s, 147483648, 11));
	}
	i = n == 147483648 && s[0] == '-' ? 2 : 0;
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
		i++;
	}
	while (--len >= i)
	{
		s[len] = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}

char		*ft_itoa(int n)
{
	int		len;
	int		len_check;
	char	*char_n;

	len_check = n;
	len = 1;
	while (len_check < -9 || len_check > 9)
	{
		len_check = len_check / 10;
		len++;
	}
	if (n < 0)
		len++;
	char_n = (char *)malloc(sizeof(char) * (len + 1));
	if (!char_n)
		return (NULL);
	return (int_to_char(char_n, n, len));
}
