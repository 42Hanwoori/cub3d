/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 07:00:55 by ji-park           #+#    #+#             */
/*   Updated: 2021/03/18 03:40:50 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int split_len(char **split)
{
	int i;

	i = 0;
	while (split[i] != 0)
	{
		i++;
	}
	return (i);
}

int exit_error(t_info *info)
{
	ft_putstr("Error\n");
	if (info->fd)
		close(info->fd);
	exit(0);
	return (-1);
}

void ft_free_split(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int is_dir(char c)
{
	if (c == 'N' || c == 'S' ||
		c == 'W' || c == 'E')
		return (1);
	return (-1);
}

int is_map_arg(char c)
{
	if (is_dir(c) == 1 || c == ' ' ||
		(c >= '0' && c <= '2') ||
		c == '\n' || c == '\0')
		return (1);
	return (-1);
}

int		check_init(t_info *info)
{
	if (!info->width || !info->height || !info->map_width ||\
		!info->map_height || !info->north ||\
		!info->south || !info->west ||\
		!info->east || !info->sprite_texture)
		return (exit_error(info));
	return (1);
}