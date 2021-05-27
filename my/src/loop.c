#include "cub3d.h"

int		key_release(int key_code, t_player *player)
{
	if (key_code == KEY_W)
		player->walk_dir = 0;
	else if (key_code == KEY_A)
	{
		player->walk_dir = 0;
		player->left_move = 0;
	}
	else if (key_code == KEY_S)
		player->walk_dir = 0;
	else if (key_code == KEY_D)
	{
		player->walk_dir = 0;
		player->right_move = 0;
	}
	else if (key_code == KEY_LEFT)
		player->turn_dir = 0;
	else if (key_code == KEY_RIGHT)
		player->turn_dir = 0;
	return (1);
}

int		key_press(int key_code, t_set *set)
{
	if (key_code == KEY_W)
		set->player.walk_dir = 1;
	else if (key_code == KEY_A)
	{
		set->player.walk_dir = 1;
		set->player.left_move = 1;
	}
	else if (key_code == KEY_S)
		set->player.walk_dir = -1;
	else if (key_code == KEY_D)
	{
		set->player.walk_dir = 1;
		set->player.right_move = 1;
	}
	else if (key_code == KEY_LEFT)
		set->player.turn_dir = -1;
	else if (key_code == KEY_RIGHT)
		set->player.turn_dir = 1;
	else if (key_code == KEY_ESC)
		ft_close();
	return (1);
}

void	update_player(t_set *set, t_player *player)
{
	int		move;
	float	new_x;
	float	new_y;
	double	move_angle;

	move = player->walk_dir * player->walk_speed;
	player->player_angle += player->turn_dir * player->turn_speed;
	move_angle = player->player_angle;
	if (player->left_move == 1)
		move_angle = player->player_angle + (PI / 2 * 3);
	else if (player->right_move == 1)
		move_angle = player->player_angle + (PI / 2);
	new_x = player->x + cos(move_angle) * move;
	new_y = player->y + sin(move_angle) * move;
	if (!inside_wall(set, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

int		main_loop(t_set *set)
{
	update_player(set, &set->player);
	mlx_clear_window(set->mlx, set->win);
	clear_window(set);
	ray_casting(set);
	draw_3d_wall(set);
	draw_sprite(set);
	mlx_put_image_to_window(set->mlx, set->win, set->img.img, 0, 0);
	return (0);
}

int		process_program(t_set *set)
{
	set->win = mlx_new_window(set->mlx, set->width, set->height,
	"win_for_cub3D");
	mlx_hook(set->win, X_EVENT_KEY_PRESS, 0, &key_press, set);
	mlx_hook(set->win, X_EVENT_KEY_RELEASE, 0, &key_release, &(set->player));
	mlx_hook(set->win, X_EVENT_KEY_EXIT, 0, &ft_close, set);
	mlx_loop_hook(set->mlx, &main_loop, set);
	mlx_loop(set->mlx);
	return (0);
}
