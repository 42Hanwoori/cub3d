#include "cub3d.h"

void	set_sprite_position(t_set *set, t_sprite *sprite)
{
	float	sprite_angle;
	float	correct_dist;

	correct_dist = sprite->distance * cos(sprite->angle);
	sprite->height = (TILE_SIZE / correct_dist) * set->wall.dist_to_win;
	sprite->width = sprite->height;
	sprite->top_y = (set->height / 2) - (sprite->height / 2);
	if (sprite->top_y < 0)
		sprite->top_y = 0;
	sprite->bottom_y = (set->height / 2) + (sprite->height / 2);
	if (sprite->bottom_y > set->height)
		sprite->bottom_y = set->height;
	
	sprite_angle = atan2(sprite->y - set->player.y, sprite->x - set->player.x) - set->player.player_angle;
	sprite->screen_pos_x = tan(sprite_angle) * set->wall.dist_to_win - sprite->width / 2;
	sprite->left_x = (set->width / 2) + sprite->screen_pos_x;
	sprite->right_x = sprite->left_x + sprite->width;
}
