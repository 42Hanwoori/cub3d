#include "cub3d.h"

int		inside_wall(t_set *set, double next_x, double next_y)
{
	int map_x;
	int map_y;

	if (next_x < 0 || next_x > (TILE_SIZE * set->map_width) ||
	next_y < 0 || next_y > (set->map_height * TILE_SIZE))
		return (1);
	map_x = floor(next_x / TILE_SIZE);
	map_y = floor(next_y / TILE_SIZE);
	if (set->map[map_y][map_x] == '1' || set->map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

void	wall_init(t_set *set, t_wall *wall, int i)
{
	set->wall.corr_wall_dist = set->ray[i].wall_distance *
	cos(set->ray[i].ray_angle - set->player.player_angle);
	wall->proj_wall_height = (TILE_SIZE / wall->corr_wall_dist) *
	wall->dist_to_win;
	wall->wall_height_in_win = (int)wall->proj_wall_height;
	wall->wall_strip_y_top = (set->height / 2) - (wall->wall_height_in_win / 2);
	if (wall->wall_strip_y_top < 0)
		wall->wall_strip_y_top = 0;
	wall->wall_strip_y_bottom = (set->height / 2) +
	(wall->wall_height_in_win / 2);
	if (wall->wall_strip_y_bottom > set->height)
		wall->wall_strip_y_bottom = set->height;
}

int		texture_by_wall_dir(t_set *set, int x, int y, int i)
{
	if (set->ray[i].was_hit_vertical)
	{
		if (set->ray[i].ray_facing_left)
			return ((set->texture)[1][TEXTURE_WIDTH * y + 64 - x - 1]);
		else
			return ((set->texture)[0][TEXTURE_WIDTH * y + x]);
	}
	else
	{
		if (set->ray[i].ray_facing_up)
			return ((set->texture)[3][TEXTURE_WIDTH * y + x]);
		else
			return ((set->texture)[2][TEXTURE_WIDTH * y + 64 - x - 1]);
	}
}

void	draw_strip_in_wall(t_set *set, t_wall *wall, int *y, int i)
{
	int	texel_color;
	int	tex_offset_y;
	int tex_offset_x;
	int	dist_from_top;

	tex_offset_x = (int)set->ray[i].wall_hit_x % TILE_SIZE;
	if (set->ray[i].was_hit_vertical)
		tex_offset_x = (int)set->ray[i].wall_hit_y % TILE_SIZE;
	dist_from_top = *y + (wall->wall_height_in_win / 2) - (set->height / 2);
	tex_offset_y = dist_from_top * ((float)TEXTURE_HEIGHT /
	wall->wall_height_in_win);
	texel_color = texture_by_wall_dir(set, tex_offset_x, tex_offset_y, i);
	set->img.data[(set->width * *y) + i] = texel_color;
	if (wall->dist_to_win > 0)
		(*y)++;
}

void	draw_3d_wall(t_set *set)
{
	int			i;
	int			y;
	int			ceiling;
	int			floor;

	ceiling = cal_floor_ceiling_color(set->ceiling_color);
	floor = cal_floor_ceiling_color(set->floor_color);
	i = -1;
	set->wall.dist_to_win = (set->width / 2) / tan(set->fov / 2);
	while (++i < set->width)
	{
		y = -1;
		wall_init(set, &set->wall, i);
		while (++y < set->wall.wall_strip_y_top)
			set->img.data[(set->width * y) + i] = ceiling;
		while (y < set->wall.wall_strip_y_bottom)
			draw_strip_in_wall(set, &set->wall, &y, i);
		while (y < set->height)
			set->img.data[(set->width * y++) + i] = floor;
	}
}
