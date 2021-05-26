#include "cub3d.h"

int		inside_wall(t_set *set, double next_x, double next_y)
{
	int map_x;
	int map_y;

	if(next_x < 0 || next_x > (TILE_SIZE * set->map_width) || next_y < 0 || next_y > (set->map_height * TILE_SIZE))
		return (1);
	map_x = floor(next_x / TILE_SIZE);
	map_y = floor(next_y / TILE_SIZE);
	if (set->map[map_y][map_x] == '1' || set->map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

void	wall_init(t_set *set, t_wall *wall, int i)
{
	set->wall.corr_wall_dist = set->ray[i].wall_distance * cos(set->ray[i].ray_angle - set->player.player_angle);
	wall->proj_wall_height = (TILE_SIZE / wall->corr_wall_dist) * wall->dist_to_win;
	wall->wall_height_in_win = (int)wall->proj_wall_height;
	wall->wall_strip_y_top = (set->height / 2) - (wall->wall_height_in_win / 2);
	if (wall->wall_strip_y_top < 0)
		wall->wall_strip_y_top = 0;	
	wall->wall_strip_y_bottom = (set->height / 2) + (wall->wall_height_in_win / 2);
	if (wall->wall_strip_y_bottom > set->height)
		wall->wall_strip_y_bottom = set->height;
}

int		texture_by_wall_dir(t_set *set, int x, int y, int i)
{
	if (set->ray[i].was_hit_vertical) // 동 or 서
	{
		if (set->ray[i].ray_facing_left) //서
			return ((set->texture)[1][TEXTURE_WIDTH * y + 64 - x - 1]);
		else // 동 
			return ((set->texture)[0][TEXTURE_WIDTH * y + x]);
	}
	else // 남 or 북
	{
		if (set->ray[i].ray_facing_up)//북
			return ((set->texture)[3][TEXTURE_WIDTH * y + x]);
		else // 남
			return ((set->texture)[2][TEXTURE_WIDTH * y + 64 - x - 1]);
	}
}

void	draw_strip_in_wall(t_set *set, t_wall *wall, int *y, int i)//텍스쳐의 특정 위치에 있는 픽셀을 가져온다
{
	int	texel_color;
	int	texture_offset_y;
	int texture_offset_x;
	int	dist_from_top;

	texture_offset_x = (int)set->ray[i].wall_hit_x % TILE_SIZE;
	if (set->ray[i].was_hit_vertical)
		texture_offset_x = (int)set->ray[i].wall_hit_y % TILE_SIZE;	
	dist_from_top = *y + (wall->wall_height_in_win / 2) - (set->height / 2);
	texture_offset_y = dist_from_top * ((float)TEXTURE_HEIGHT / wall->wall_height_in_win);
	texel_color = texture_by_wall_dir(set, texture_offset_x, texture_offset_y, i);
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
	floor =  cal_floor_ceiling_color(set->floor_color);
	i = -1;
	set->wall.dist_to_win = (set->width / 2) / tan(FOV / 2);
	while (++i < set->width)
	{
		y = -1;
		wall_init(set, &set->wall, i);//레이에서 그려질 벽의 높이, 시작-끝지점, fish-bowl방지용 벽까지의 거리 조정
		while (++y < set->wall.wall_strip_y_top)
		  	set->img.data[(set->width * y) + i] = ceiling;
		while (y < set->wall.wall_strip_y_bottom)
			draw_strip_in_wall(set, &set->wall, &y, i);
		while (y < set->height)
			set->img.data[(set->width * y++) + i] = floor;
	}
}
