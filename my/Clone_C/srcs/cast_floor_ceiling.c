/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 04:07:27 by ji-park           #+#    #+#             */
/*   Updated: 2021/03/18 01:21:59 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_floor_ceiling(t_info *info)
{
	int y;
	int x;
    int floor_color;
    int ceiling_color;
    
    floor_color = (info->floor_color.red * 256 * 256) \
	+ (info->floor_color.green * 256) + (info->floor_color.blue);
    ceiling_color = (info->ceiling_color.red * 256 * 256) + \
	(info->ceiling_color.green * 256) + (info->ceiling_color.blue);
	y = -1;
	while (++y < info->height)
	{
		x = -1;
		while (++x < info->width)
		{
			if (y > info->height / 2)
				info->buf[y][x] = floor_color;
			else
				info->buf[y][x] = ceiling_color;
		}
	}
}
