/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:27:17 by ji-park           #+#    #+#             */
/*   Updated: 2021/03/15 20:39:09 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int up_test(t_info *info, int i, int j)
{
    while (i >= 0)
    {
        if (info->map[i][j] == '1')
            return (1);
        i--;
    }
    return (0);
}

int down_test(t_info *info, int i, int j)
{
    while (i < info->map_height)
    {
        if (info->map[i][j] == '1')
            return (1);
        i++;
    }
    return (0);
}

int left_test(t_info *info, int i, int j)
{
    while (j >= 0)
    {
        if (info->map[i][j] == '1')
            return (1);
        j--;
    }
    return (0);
}

int rigth_test(t_info *info, int i, int j)
{
    while (j < info->map_width)
    {
        if (info->map[i][j] == '1')
            return (1);
        j++; 
    }
    return (0);
}