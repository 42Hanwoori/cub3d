/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:56:18 by whan              #+#    #+#             */
/*   Updated: 2020/11/05 16:01:14 by whan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_and_free_all(char **s, char *sen, int i)
{
	int n;

	n = 0;
	if (!sen)
	{
		while (n <= i)
			free(s[n++]);
		free(s);
		return (0);
	}
	return (1);
}

static void		fill_inside(char *pocket, int start, int end, const char *ingrd)
{
	int i;

	i = 0;
	while (start < end)
		pocket[i++] = ingrd[start++];
	pocket[i] = 0;
}

static char		**fill_in(char const *s, char c, char **draw)
{
	int		order;
	int		i;
	int		j;

	order = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (i < (int)ft_strlen(s) && s[i] != c)
				i++;
			draw[order] = (char *)malloc(sizeof(char) * (i - j + 1));
			if (!check_and_free_all(draw, draw[order], order))
				return (NULL);
			fill_inside(draw[order], j, i, s);
			order++;
		}
		else
			i++;
	}
	return (draw);
}

static size_t	how_many(char const *s, char c)
{
	size_t	i;
	size_t	n;

	i = -1;
	n = 0;
	while (s[++i])
	{
		if (s[i] != c && s[i + 1] == c)
			n += 1;
		else if (s[i] != c && i + 1 == ft_strlen(s))
			n += 1;
	}
	return (n);
}

char			**ft_split(char const *s, char c)
{
	size_t	len;
	char	**spt_s;

	len = how_many(s, c);
	spt_s = (char **)malloc(sizeof(char *) * (len + 1));
	if (!spt_s)
		return (NULL);
	if (!fill_in(s, c, spt_s))
		return (NULL);
	spt_s[len] = (0);
	return (spt_s);
}
