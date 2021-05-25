/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_before_map2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 02:44:00 by ji-park           #+#    #+#             */
/*   Updated: 2021/03/18 02:47:39 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    get_floor(t_color *color, char **splits)
{
    color->red = ft_atoi(splits[0]);
    color->green = ft_atoi(splits[1]);
    color->blue = ft_atoi(splits[2]);
}

void    get_ceiling(t_color *color, char **splits)
{
    color->red = ft_atoi(splits[0]);
    color->green = ft_atoi(splits[1]);
    color->blue = ft_atoi(splits[2]);
}

int check_info(t_info *info,char **splits)
{
    if (ft_strcmp(*splits, "R") == 0)
        return (get_screen_size(info, splits));
    if (ft_strcmp(*splits, "SO") == 0)
        return (get_texture(info, splits));
    if (ft_strcmp(*splits, "NO") == 0)
        return (get_texture(info, splits));
    if (ft_strcmp(*splits, "WE") == 0)
        return (get_texture(info, splits));
    if (ft_strcmp(*splits, "EA") == 0)
        return (get_texture(info, splits));
    if (ft_strcmp(*splits, "S") == 0)
        return (get_texture(info, splits));
    if (ft_strcmp(*splits, "F") == 0)
        return (get_color(info, splits));
    if (ft_strcmp(*splits, "C") == 0)
        return (get_color(info, splits));
    else if (*splits[0] == '\0')
		return (0);
    return (1); 
}

int check_complete(t_info *info)
{
    if (info->width != 0 && info->height != 0 \
    && info->north != 0 \
    && info->south != 0 && info->west != 0 \
    && info->east != 0 \
    && info->sprite_texture != 0 \
    && info->floor_color.red != -1 \
    && info->floor_color.green != -1 \
    && info->floor_color.blue != -1 \
    && info->ceiling_color.red != -1 \
    && info->ceiling_color.green != -1 \
    && info->ceiling_color.blue != -1)
        return (1);
    return (0);
}
