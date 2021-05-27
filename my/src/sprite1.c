#include "cub3d.h"

void	draw_sprite_by_stripe(t_set *set, t_sprite *sprite, int x, int y)
{
	int		dist_from_top;
	float	texel_width;
	int		texel_color;

	texel_width = (float)(TEXTURE_WIDTH / sprite->width);
	sprite->tex_offset_x = (x - sprite->left_x) * texel_width;
	while (++y < sprite->bottom_y)
	{
		if (x > 0 && x < set->width && y > 0 && y < set->height)
		{
			dist_from_top = y + (sprite->height / 2) - (set->height / 2);
			sprite->tex_offset_y = dist_from_top * (TEXTURE_HEIGHT / \
			sprite->height);
			if (TEXTURE_WIDTH * sprite->tex_offset_y + \
			sprite->tex_offset_x == -1)
				continue;
			texel_color = set->texture[4][TEXTURE_WIDTH *\
			sprite->tex_offset_y + sprite->tex_offset_x];
			if (texel_color != 0x000000)
			{
				if (set->ray[x].wall_distance > sprite->distance)
					set->img.data[set->width * y + x] = texel_color;
			}
		}
	}
}

void	draw_visible_sprites(t_set *set)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (++i < set->num_sprite)
	{
		if (set->sprite[i].visible == 1)
		{
			set_sprite_position(set, &(set->sprite[i]));
			x = set->sprite[i].left_x - 1;
			y = set->sprite[i].top_y - 1;
			while (++x < set->sprite[i].right_x)
				draw_sprite_by_stripe(set, &set->sprite[i], x, y);
		}
	}
}

void	check_visible_sprites(t_set *set, int i)
{
	float	angle_sprite_player;
	float	epsilon;

	i = -1;
	epsilon = 0.2;
	while (++i < set->num_sprite)
	{
		angle_sprite_player = normalize_angle(set->player.player_angle)\
		- atan2(set->sprite[i].y - set->player.y, set->sprite[i].x -\
		set->player.x);
		if (angle_sprite_player > PI)
			angle_sprite_player -= PI * 2;
		if (angle_sprite_player < -PI)
			angle_sprite_player += PI * 2;
		angle_sprite_player = fabs(angle_sprite_player);
		if (angle_sprite_player < set->fov / 2 + epsilon)
		{
			set->sprite[i].visible = 1;
			set->sprite[i].angle = angle_sprite_player;
			set->sprite[i].distance = dbt(set->sprite[i].x, \
			set->sprite[i].y, set->player.x, set->player.y);
		}
		else
			set->sprite[i].visible = 0;
	}
}

void	rearrange_sprites_by_dist(t_set *set, t_sprite *sprite)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = -1;
	while (++i < set->num_sprite)
	{
		if (sprite[i].visible == 1)
		{
			j = i + 1;
			while (j < set->num_sprite)
			{
				if (sprite[j].visible == 1 && sprite[j].distance > \
				sprite[i].distance)
				{
					temp = sprite[i];
					sprite[i] = sprite[j];
					sprite[j] = temp;
				}
				j++;
			}
		}
	}
}

void	draw_sprite(t_set *set)
{
	check_visible_sprites(set, 0);
	rearrange_sprites_by_dist(set, set->sprite);
	draw_visible_sprites(set);
}
