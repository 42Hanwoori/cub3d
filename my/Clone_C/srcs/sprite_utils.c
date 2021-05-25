/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:34:46 by ji-park           #+#    #+#             */
/*   Updated: 2021/03/18 01:26:11 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		get_max_line_size(t_list *lst)
{
	int		max;
	int		size;

	max = 0;
	while (lst)
	{
		size = ft_strlen((char *)lst->content);
		if (size > max)
			max = size;
		lst = lst->next;
	}
	return (max);
}

void	sort(t_info *info)
{
	int			i;
	int			j;
	int			max;
	t_sprite	temp;

	i = 0;
	max = 0;
	while (i < info->num_sprite - 1)
	{
		max = i;
		j = i + 1;
		while (j < info->num_sprite)
		{
			if (info->sprite[j].distance > info->sprite[i].distance)
				max = j;
			j++;
		}
		if (i != max)
		{
			temp = info->sprite[i];
			info->sprite[i] = info->sprite[max];
			info->sprite[max] = temp;
		}
		i++;
	}
}

void set_pos_sprite(t_info *info, int x, int y,int i)
{
    info->sprite[i].x = 0.5f * x;
    info->sprite[i].y = 0.5f * y;
}

int set_sprite(t_info *info)
{
    int x;
    int y;
    int i;

    y = 0;
    i = 0;
    info->sprite = (t_sprite *)malloc(sizeof(t_sprite) * info->num_sprite);
    if (info->sprite == 0)
        return(exit_error(info));
    while (y < info->map_height)
    {
        x = 0;
        while (x < info->map_height)
        {
            if (info->map[x][i] == '2')
            {
                set_pos_sprite(info, x, y, i);
                i++;
            }
            x++;
        }
        y++;
    }
    return (1);
}