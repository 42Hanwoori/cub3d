/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 22:31:34 by whan              #+#    #+#             */
/*   Updated: 2020/11/02 17:38:17 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		inset(char const *set, char check)
{
	int i;

	i = -1;
	while (set[++i])
		if (set[i] == check)
			return (1);
	return (0);
}

static size_t	find_begin(char const *sen, char const *set)
{
	size_t	i;

	i = 0;
	while (sen[i] && inset(set, sen[i]))
		i++;
	return (i);
}

static size_t	find_end(char const *sen, char const *set)
{
	size_t	i;

	i = 0;
	while (sen[i])
		i++;
	while (inset(set, sen[i - 1]) && i > 0)
		i--;
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*tsen;
	size_t	len;
	size_t	begin;
	size_t	end;
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (0);
	begin = find_begin(s1, set);
	if (begin == ft_strlen(s1))
		return (ft_strdup(""));
	end = find_end(s1, set);
	len = end - begin;
	tsen = (char *)malloc(sizeof(char) * (len + 1));
	if (!tsen)
		return (NULL);
	while (i < len)
	{
		tsen[i] = s1[begin++];
		i++;
	}
	tsen[i] = 0;
	return (tsen);
}
