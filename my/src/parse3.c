#include "cub3d.h"

int		check_complete(t_set *set)
{
	if (set->width != -1 && set->height != -1 \
	&& set->north != 0 \
	&& set->south != 0 && set->west != 0 \
	&& set->east != 0 \
	&& set->sprite_texture != 0 \
	&& set->floor_color.red != -1 \
	&& set->floor_color.green != -1 \
	&& set->floor_color.blue != -1 \
	&& set->ceiling_color.red != -1 \
	&& set->ceiling_color.green != -1 \
	&& set->ceiling_color.blue != -1)
		return (1);
	return (0);
}

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

int		check_init(t_set *set)
{
	if (!set->width || !set->height || !set->map_width ||\
		!set->map_height || !set->north ||\
		!set->south || !set->west ||\
		!set->east || !set->sprite_texture)
		return (exit_error(set, "not initiated enough"));
	return (1);
}

int		set_sprite(t_set *set)
{
	int	i;
	int	j;
	int sp_count;

	sp_count = 0;
	if (!(set->sprite = (t_sprite *)malloc(sizeof(t_sprite) * set->num_sprite)))
		return (0);
	i = -1;
	while (++i < set->map_height)
	{
		j = -1;
		while (++j < set->map_width)
		{
			if (set->map[i][j] == '2')
			{
				set->sprite[sp_count].x = (0.5f + j) * TILE_SIZE;
				set->sprite[sp_count++].y = (0.5f + i) * TILE_SIZE;
			}
		}
	}
	return (1);
}
