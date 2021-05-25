/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_before_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:03:33 by ji-park           #+#    #+#             */
/*   Updated: 2021/03/18 03:42:01 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_screen_size(t_info *info, char **splits)
{
    int max_width = 1024;
	int max_height = 1024;

    if (split_len(splits) != 3)
        return(-1);
    info->width = ft_atoi(splits[1]);
    info->height = ft_atoi(splits[2]);
    if (info->width == 0 || info->height == 0)
		return (-1);
    if (info->width > max_width)
        info->width = max_width;
    if (info->height > max_height)
        info->height = max_width;
    return (0); 
}

int    get_texture(t_info *info, char **splits)
{
    if (split_len(splits) != 2)
        return(-1);
    if (ft_strcmp(splits[0], "NO") == 0)
		info->north = ft_strdup(splits[1]);
	else if (ft_strcmp(splits[0], "SO") == 0)
		info->south = ft_strdup(splits[1]);
	else if (ft_strcmp(splits[0], "WE") == 0)
		info->west = ft_strdup(splits[1]);
	else if (ft_strcmp(splits[0], "EA") == 0)
		info->east = ft_strdup(splits[1]);
	else if (ft_strcmp(splits[0], "S") == 0)
		info->sprite_texture = ft_strdup(splits[1]);
	return (0);  
}

int   get_color(t_info *info, char **splits)
{
    char **color;

    if (split_len(splits) != 2)
        return(-1);
    color = ft_split(splits[1],',');
    if (split_len(color) != 3)
        return(-1);
    if (ft_strcmp(splits[0],"F") == 0)
        get_floor(&info->floor_color, color);
    else if (ft_strcmp(splits[0],"C") == 0)
        get_ceiling(&info->ceiling_color, color);
    return (0);
}

int     parse_line(t_info *info ,char *line)
{
    char **splits;

    splits = ft_split(line, ' ');
    if (*splits == 0)
        return (0);
    else
        return (check_info(info, splits));
}

int parse_cub(t_info *info, char *path)
{
    char    *line;

    init_info(info, &info->floor_color, &info->ceiling_color);
    info->fd = open(path, O_RDONLY);
    while (get_next_line(info->fd, &line) > 0)
    {
        if ((parse_line(info, line)) == -1)
            return (exit_error(info));
        free(line);
        line = 0;
        if ((check_complete(info)) == 1)
            break; 
    }
    if (!read_map(info, line))
        return (exit_error(info));
    if (!check_init(info))
		return (exit_error(info));
    if (!set_sprite(info))
        return (exit_error(info));
    return (1);
}