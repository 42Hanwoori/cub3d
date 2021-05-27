#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = 10;
	player->y = 10;
	player->rad = 4;
	player->walk_dir = 0;
	player->turn_dir = 0;
	player->walk_speed = 20;
	player->turn_speed = 2 * (PI / 180);
	player->right_move = 0;
	player->left_move = 0;
}

void	init_info(t_set *set, t_color *color, t_color *color2)
{
	set->width = 0;
	set->height = 0;
	set->map_width = 0;
	set->map_height = 0;
	set->map = 0;
	set->north = 0;
	set->south = 0;
	set->west = 0;
	set->east = 0;
	set->sprite_texture = 0;
	set->sprite = 0;
	set->num_sprite = 0;
	set->fov = 60 * PI / 180;
	color->red = -1;
	color->green = -1;
	color->blue = -1;
	color2->red = -1;
	color2->green = -1;
	color2->blue = -1;
}

void	init_direction(t_set *set, int i, int j, int *dir_count)
{
	if (is_dir(set->map[i][j]) == 1)
	{
		set->dir = set->map[i][j];
		set->player.x = (0.5 + j) * TILE_SIZE;
		set->player.y = (0.5 + i) * TILE_SIZE;
		(*dir_count)++;
	}
	if (set->map[i][j] == '2')
		set->num_sprite++;
}

void	init_player_direction(t_set *set)
{
	int angle;
	int direction;

	angle = 0;
	direction = set->dir;
	if (direction == 'S')
		angle = 90;
	else if (direction == 'N')
		angle = 270;
	else if (direction == 'E')
		angle = 0;
	else if (direction == 'W')
		angle = 180;
	set->player.player_angle = angle * (PI / 180);
}
