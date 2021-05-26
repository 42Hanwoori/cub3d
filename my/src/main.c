#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "../library/libft/libft.h"
#include "../library/libft/get_next_line.h"
#include "../library/mlx/mlx.h"
#include <float.h>
#include <fcntl.h>
#include <errno.h>
#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_RELEASE		3
#define X_EVENT_KEY_EXIT		17 //Exit program key code

#define KEY_ESC					53
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2

# define PI 					3.1415926535897
# define FOV 					(60 * PI / 180)
# define TILE_SIZE 				64
# define MINI 					0.2
# define F_MAX					FLT_MAX
# define rad(d)					(d) * (M_PI / 180)
# define TEXTURE_WIDTH			64
# define TEXTURE_HEIGHT			64

typedef struct	s_img
{
	void						*img;
	int							*data;
	
	int							width;
	int							height;
	int							size_l;
	int							bpp;
	int							endian;
}								t_img;

typedef struct s_ray
{
	double						ray_angle;
	int							ray_facing_up;
	int							ray_facing_down;
	int							ray_facing_left;
	int							ray_facing_right;
	double						x_intercept;
	double						y_intercept;
	double						x_step;
	double						y_step;
	double						h_dist;
	double						v_dist;
	double 						wall_hit_x;
	double						wall_hit_y;
	double 						wall_distance;
	int							found_horz_wall_hit;
	int							found_vert_wall_hit;
	int							was_hit_vertical;
}								t_ray;

typedef struct 	s_wall
{
	float						corr_wall_dist;
	double						dist_to_win;
	int							wall_height_in_win;
	int							wall_strip_y_top;
	int							wall_strip_y_bottom;
	float						proj_wall_height;
}								t_wall;

typedef struct s_player
{
	float						x;
	float						y;
	float 						rad;
	float						player_angle; // 현 각도
	int							right_move;
	int							left_move;
	int							walk_dir;
	int							turn_dir;
	float						walk_speed;
	float						turn_speed;
}								t_player;

typedef struct s_color
{
	int							red;
	int							green;
	int							blue;
}								t_color;

typedef struct s_sprite
{
	int							i;
	double						x;
	double						y;
	double						distance;
	double						angle;
	float						height;
	float						width;
	float						top_x;
	float						top_y;
	float						bottom_x;
	float						bottom_y;
	float						left_x;
	float						right_x;
	int							texutre_offset_x;
	int							texutre_offset_y;
	double						screen_pos_x;
	int							visible;
	int							texture;
}								t_sprite;

typedef struct	s_set
{
	void						*mlx;
	void						*win;
	t_img						img;

	t_player					player;
	t_ray						*ray;
	t_wall						wall;
	t_sprite					*sprite;
	int							**texture;
	int							fd;
	int							width;
	int							height;
	int							map_width;
	int							map_height;
	char						**map;
	char						*north;
	char						*south;
	char						*west;
	char						*east;
	char						*sprite_texture;
	t_color						floor_color;
	t_color						ceiling_color;
	int							dir;
	int							num_sprite;
	int							**buffer;
}								t_set;

void	free_double_array(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	ft_putstr(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int exit_error(t_set *set)
{
	ft_putstr("Error\n");
	if (set->fd)
		close(set->fd);
	exit(1);
}

int	cal_floor_ceiling_color(t_color color)
{
	int	res;

	res = (color.red * 256 * 256) + (color.green * 256) + color.blue;
	return (res);
}

int		num_only(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}

int	split_len(char **split)
{
	int i;

	i = 0;
	while (split[i] != 0)
	{
		i++;
	}
	return (i);
}

void	ft_free(void *s)
{
	free(s);
	s = 0;
}

int		ft_close(void)
{
	exit(0);
	return (0);
}

int	up_test(t_set *set, int i, int j)
{
	while (i >= 0)
	{
		if (set->map[i][j] == '1')
			return (1);
		if (set->map[i][j] == ' ')
			return (0);
		i--;
	}
	return (0);
}

int	down_test(t_set *set, int i, int j)
{
	while (i < set->map_height)
	{
		if (set->map[i][j] == '1')
			return (1);
		if (set->map[i][j] == ' ')
			return (0);
		i++;
	}
	return (0);
}

int	left_test(t_set *set, int i, int j)
{
	while (j >= 0)
	{
		if (set->map[i][j] == '1')
			return (1);
		if (set->map[i][j] == ' ')
			return (0);
		j--;
	}
	return (0);
}

int	rigth_test(t_set *set, int i, int j)
{
	while (j < set->map_width)
	{
		if (set->map[i][j] == '1')
			return (1);
		if (set->map[i][j] == ' ')
			return (0);
		j++; 
	}
	return (0);
}

int	is_dir(char c)
{
	if (c == 'N' || c == 'S' ||
		c == 'W' || c == 'E')
		return (1);
	return (-1);
}

int	is_map_arg(char c)
{
	if (is_dir(c) == 1 || c == ' ' ||
		(c >= '0' && c <= '2') ||
		c == '\n' || c == '\0')
		return (1);
	return (-1);
}

int		ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] != 0 || str2[i] != 0)
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (1);
		i++;
	}
	return (0);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t i;

// 	i = 0;
// 	while (str[i] != 0)
// 		i++;
// 	return (i);
// }

int		check_extension(char *s, char *s_ext)
{
	size_t	i;
	
	i = 0;
	while (s[i])
		i++;
	if (i >= ft_strlen(s_ext))
	{
		i -= ft_strlen(s_ext);
		if (ft_strcmp(&s[i], s_ext) == 0)
			return (1);
	}
	return (0);
}


void	draw_player_nose(t_set *set)
{
	int	i;
	int	size;
	int dx;
	int	dy;

	i = 0;
	size = 20;
	while(++i <= size)
	{
		dx = set->player.x * MINI + cos(set->player.player_angle) * i;
		dy = set->player.y * MINI + sin(set->player.player_angle) * i;
		set->img.data[(set->width) * dy + dx] = 0xAA00FF00;
	}
}

void	render_ray(t_set *set, t_ray *ray)
{
	int		i;
	int		ray_piece_x;
	int		ray_piece_y;

	i = -1;
	while (++i < ray->wall_distance * MINI)
	{
		ray_piece_x = set->player.x * MINI + cos(ray->ray_angle) * i;
		ray_piece_y = set->player.y * MINI + sin(ray->ray_angle) * i;
		set->img.data[(set->width) * ray_piece_y + ray_piece_x] = 0xAAFF0000;
	}
}

void	draw_player(t_set *set)
{
	int		x;
	int		y;
	int		size;
	int		angle_count;

	angle_count = 0;
	while (angle_count < 360)
	{
		size = 0;
		while (size < set->player.rad)
		{
			x = (set->player.x * MINI + cos(rad(angle_count)) * size);
			y = (set->player.y * MINI + sin(rad(angle_count)) * size);
			set->img.data[set->width * y + x] = 0xAAFFFF00;
			size++;
		}
		angle_count++;
	}
	angle_count = -1;
	while (++angle_count < set->width)
	{
		if (angle_count % 1 == 0)
			render_ray(set, &set->ray[angle_count]);
	}
	draw_player_nose(set);
}

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

void	draw_white_rectangle(t_set *set, int x, int y) // ij = (0,1), xy = (1,0)
{
	int i;
	int j;

	x *= TILE_SIZE * MINI;
	y *= TILE_SIZE * MINI;
	i = 0;
	while (i < TILE_SIZE * MINI)
	{
		j = 0;
		while (j < TILE_SIZE * MINI)
		{
			set->img.data[((y + i) * set->width) + x + j] = 0xAAFFFFFF;
			j++;
		}
		i++;
	}
}

void	draw_black_rectangle(t_set *set, int x, int y) // ij = (0,1), xy = (1,0)
{
	int i;
	int j;

	x *= TILE_SIZE * MINI;
	y *= TILE_SIZE * MINI;
	i = 0;
	while (i < TILE_SIZE * MINI)
	{
		j = 0;
		while (j < TILE_SIZE * MINI)
		{
			set->img.data[((y + i) * set->width) + x + j] = 0xAA000000;
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_set *set)
{
	int		i;
	int		j;

	i = 0;
	while (i < set->map_height)
	{
		j = 0;
		while (j < set->map_width)
		{
			if (set->map[i][j] == '1')
				draw_white_rectangle(set, j, i);
			else
				draw_black_rectangle(set, j, i);
			j++;
		}
		i++;
	}
	draw_player(set);
}

int		key_release(int key_code, t_player *player) // 놓은 키에 따라 해당되는 값을 적용한다.
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

float	normalize_angle(float angle) 
{
	angle = fmodf(angle, (2 * PI));
	if (angle < 0)
		angle = (2 * PI) + angle;
	return angle;
}

void	init_ray(t_ray *ray, double ray_angle) // 방향확인 for xystep 더할지 뺄지 결정
{
	ray->ray_angle = normalize_angle(ray_angle);
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->wall_distance = 0;
	ray->ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->ray_facing_up = !ray->ray_facing_down;
	ray->ray_facing_right = ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI;
	ray->ray_facing_left = !ray->ray_facing_right;
	ray->was_hit_vertical = 0;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->found_horz_wall_hit = 0;
	ray->found_vert_wall_hit = 0;
	ray->h_dist = 0;
	ray->v_dist = 0;
}

void	check_ray_hit_horz_set(t_set *set, t_ray *ray)
{
	ray->y_intercept = floor(set->player.y / TILE_SIZE) * TILE_SIZE + (ray->ray_facing_down * TILE_SIZE);
	ray->x_intercept = set->player.x + (ray->y_intercept - set->player.y) / tan(ray->ray_angle);
	ray->y_step = TILE_SIZE;
	if (ray->ray_facing_up)
		ray->y_step *= -1;
	ray->x_step = TILE_SIZE / tan(ray->ray_angle);
	if ((ray->ray_facing_left && ray->x_step > 0) || (ray->ray_facing_right && ray->x_step < 0))
		ray->x_step *= -1;
}

void	check_ray_hit_horz(t_set *set, t_ray *ray, double *wall_horz_x, double *wall_horz_y)
{
	double	next_horz_x;
	double	next_horz_y;
	double	y_to_check;

	next_horz_x = ray->x_intercept;
	next_horz_y = ray->y_intercept;
	y_to_check = ray->y_intercept;
	while (next_horz_x >=0 && next_horz_x <= set->map_width * TILE_SIZE && next_horz_y >= 0 \
	&& next_horz_y <= set->map_height * TILE_SIZE)
	{
		y_to_check = next_horz_y;
		if (ray->ray_facing_up)
			y_to_check = next_horz_y - 1;
		if (inside_wall(set, next_horz_x, y_to_check))
		{
			*wall_horz_x = next_horz_x;
			*wall_horz_y = next_horz_y;
			ray->found_horz_wall_hit = 1;
			break;
		}
		else
		{
			next_horz_x += ray->x_step;
			next_horz_y += ray->y_step;
		}
	}
}

void	check_ray_hit_vert_set(t_set *set, t_ray *ray)
{
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->x_intercept = floor(set->player.x / TILE_SIZE) * TILE_SIZE + (ray->ray_facing_right * TILE_SIZE);
	ray->y_intercept = set->player.y + ((ray->x_intercept - set->player.x) * tan(ray->ray_angle));
	ray->x_step = TILE_SIZE;
	if (ray->ray_facing_left)
		ray->x_step *= -1;
	ray->y_step = TILE_SIZE * tan(ray->ray_angle);
	if (ray->ray_facing_up && ray->y_step > 0)
		ray->y_step *= -1;
	if (ray->ray_facing_down && ray->y_step < 0)
		ray->y_step *= -1;
}

void	check_ray_hit_vert(t_set *set, t_ray *ray, double *wall_vert_x, double *wall_vert_y)
{
	double	next_vert_x;
	double	next_vert_y;
	double	x_to_check;

	next_vert_x = ray->x_intercept;
	x_to_check = ray->x_intercept;
	next_vert_y = ray->y_intercept;
	while (next_vert_x >=0 && next_vert_x <= set->map_width * TILE_SIZE && next_vert_y >= 0 \
	&& next_vert_y <= set->map_height * TILE_SIZE)
	{
		x_to_check = next_vert_x;
		if (ray->ray_facing_left)
			x_to_check = next_vert_x - 1;
		if (inside_wall(set, x_to_check, next_vert_y))
		{
			*wall_vert_x = next_vert_x;
			*wall_vert_y = next_vert_y;
			ray->found_vert_wall_hit = 1;
			break;
		}
		else
		{
			next_vert_x += ray->x_step;
			next_vert_y += ray->y_step;
		}
	}
}

double	distant_between_two(double x1, double y1, double x2, double y2)
{
	double	res;

	res =  sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return (res);
}

void	ray_cal_dda(t_set *set, t_ray *ray)
{
	double	horz_x;
	double	horz_y;
	double	vert_x;
	double	vert_y;

	check_ray_hit_horz_set(set, ray);
	check_ray_hit_horz(set, ray, &horz_x, &horz_y);
	check_ray_hit_vert_set(set, ray);
	check_ray_hit_vert(set, ray, &vert_x, &vert_y);
	ray->h_dist = distant_between_two(horz_x, horz_y, set->player.x, set->player.y);
	ray->h_dist = (ray->found_horz_wall_hit != 1) ? F_MAX : ray->h_dist;
	ray->v_dist = distant_between_two(vert_x, vert_y, set->player.x, set->player.y);
	ray->v_dist = (ray->found_vert_wall_hit != 1) ? F_MAX : ray->v_dist;
	if (ray->h_dist > ray->v_dist)
	{
		ray->wall_hit_x = vert_x;
		ray->wall_hit_y = vert_y;
		ray->wall_distance = ray->v_dist;
		ray->was_hit_vertical = 1;
	}
	else
	{
		ray->wall_hit_x = horz_x;
		ray->wall_hit_y = horz_y;
		ray->wall_distance = ray->h_dist;
	}
}

void	ray_casting(t_set *set)
{
	float 	ray_angle;
	int		ray_count;

	ray_count = -1;
	ray_angle = set->player.player_angle - (FOV / 2);
	while (++ray_count < set->width)
	{
		init_ray(&set->ray[ray_count], ray_angle);
		ray_cal_dda(set, &set->ray[ray_count]);
		ray_angle += FOV / (set->width - 1);
	}
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

void	clear_window(t_set *set)
{
	int	i;
	int	j;

	j = -1;
	while (++j < set->height)
	{
		i = -1;
		while (++i < set->width)
			set->img.data[set->width * j + i] = 0x000000;
	}
}

void	draw_sprites_in_mini_map(t_set *set)
{
	int		i;
	int		angle_count;
	int		dot;
	int		x;
	int		y;

	i = -1;
	while (++i < set->num_sprite)
	{
		angle_count = 0;
		while (angle_count < 360)
		{
			dot = 0;
			while (++dot < 5)
			{
				x = (set->sprite[i].x * MINI + cos(rad(angle_count)) * dot);
				y = (set->sprite[i].y * MINI + sin(rad(angle_count)) * dot);
				set->img.data[set->width * y + x] = 0x00FF00;
			}
			angle_count++;
		}
	}
}

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

void	draw_sprite_by_stripe(t_set *set, t_sprite *sprite, int x)
{
	int		y;
	int		dist_from_top;
	float	texel_width;
	int		texel_color;

	texel_width = (float)(TEXTURE_WIDTH / sprite->width);
	sprite->texutre_offset_x = (x - sprite->left_x) * texel_width;
	y = sprite->top_y - 1;
	while (++y < sprite->bottom_y)
	{
		if (x > 0 && x < set->width && y > 0 && y < set->height)
		{
			dist_from_top = y + (sprite->height / 2) - (set->height / 2);
			sprite->texutre_offset_y = dist_from_top * (TEXTURE_HEIGHT / sprite->height);
			texel_color = set->texture[4][TEXTURE_WIDTH * sprite->texutre_offset_y + sprite->texutre_offset_x];
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

	i = -1;
	while(++i < set->num_sprite)
	{
		if (set->sprite[i].visible == 1)
		{
			set_sprite_position(set, &(set->sprite[i]));
			x = set->sprite[i].left_x - 1;
			while (++x < set->sprite[i].right_x)
				draw_sprite_by_stripe(set, &set->sprite[i], x);
		}
	}
}

void	check_visible_sprites(t_set *set)
{
	int		i;
	float	angle_sprite_player;
	float	epsilon;

	
	i = -1;
	epsilon = 0.2;
	while(++i < set->num_sprite)
	{
		angle_sprite_player = normalize_angle(set->player.player_angle)\
		- atan2(set->sprite[i].y - set->player.y, set->sprite[i].x - set->player.x);
		if (angle_sprite_player > PI)
			angle_sprite_player -= PI * 2;
		if (angle_sprite_player < -PI)
			angle_sprite_player += PI * 2;
		angle_sprite_player = fabs(angle_sprite_player);
		if (angle_sprite_player < FOV / 2 + epsilon)
		{
			set->sprite[i].visible = 1;
			set->sprite[i].angle = angle_sprite_player;
			set->sprite[i].distance = distant_between_two(set->sprite[i].x, \
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
				if (sprite[j].visible == 1 && sprite[j].distance > sprite[i].distance)
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
	check_visible_sprites(set);
	rearrange_sprites_by_dist(set, set->sprite);
	draw_visible_sprites(set);
	draw_sprites_in_mini_map(set);
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
	draw_mini_map(set);
	mlx_put_image_to_window(set->mlx, set->win, set->img.img, 0, 0);
	// free(set->ray);
	// set->ray = NULL;
	return (0);
}

int		process_program(t_set *set)
{
	set->win = mlx_new_window(set->mlx, set->width, set->height, "win_for_cub3D");
	
	mlx_hook(set->win, X_EVENT_KEY_PRESS, 0, &key_press, set);
	mlx_hook(set->win, X_EVENT_KEY_RELEASE, 0, &key_release, &(set->player));
	mlx_hook(set->win, X_EVENT_KEY_EXIT, 0, &ft_close, set);
	mlx_loop_hook(set->mlx, &main_loop, set); // key가 release 되어 있는동안 main_loop 유지
	mlx_loop(set->mlx);
	return(0);
}

void	set_int_in_char(unsigned char *start, int value)//int는 4byte니까 1byte씩 넘기면서 넣어줌
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	write_bmp_header(t_set *set, int fd, int size)
{
	unsigned char	header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, size); // 4칸(파일 전체크기) + 4칸(사용안함)
	header[10] = (unsigned char)54;//픽셀데이터의 시작주소(숫자면 무조건 4byte)-헤더 끝나면 바로니까
	header[14] = (unsigned char)40;//~14까지가 파일에 대한 정보(헤더-총 14바이트), 15~54까지가 비트맵자체의 정보(가로세로, 색상수)를 가지고있음(40바이트)
	set_int_in_char(header + 18, set->width);//가로사이즈 in int(4byte)
	set_int_in_char(header + 22, set->height);//세로사이즈 in int(4byte)
	header[26] = (unsigned char)1;//색상판의 수. 보통1
	header[28] = (unsigned char)24;//bpp
	write(fd, header, 54);
}


void	write_data(t_set *set, int fd)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = set->height;
	pad = (4 - (set->width * 3) % 4) % 4;
	while (i >= 0)
	{
		j = 0;
		while (j < set->width)
		{
			write(fd, &(set->buffer[i][j]), 3);
			if (pad > 0)
				write(fd, &zero, pad);
			j++;
		}
		i--;
	}
}

int		save_bmp(t_set *set)
{
	int	fd;
	int	size;

	size = 54 + 4 * set->width * set->height;
	if (!(fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC)))
		exit(1);
	write_bmp_header(set, fd, size);
	write_data(set, fd);
	return (0);
}

int		process_bmp(t_set *set)
{
	set->win = mlx_new_window(set->mlx, set->width, set->height, "win_for_cub3D");
	ray_casting(set);
	draw_3d_wall(set);
	draw_sprite(set);
	draw_mini_map(set);
	mlx_put_image_to_window(set->mlx, set->win, set->img.img, 0, 0);
	if (!save_bmp(set))
		return (exit_error(set));
	//ft_exit(0);
	return (0);
}



//process
//=================================================================================
//parse



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
	color->red = -1;
	color->green = -1;
	color->blue = -1;
	color2->red = -1;
	color2->green = -1;
	color2->blue = -1;
}

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


int	get_screen_size(t_set *set, char **splits)
{
	int max_width;
	int max_height;
	
	mlx_get_screen_size(set->mlx, &max_width, &max_height);
	if ((set->width != 0 && set->height != 0) || (split_len(splits) != 3)\
	 || !(num_only(splits[1]) && num_only(splits[2])) \
	 || splits[1][0] == '0' || splits[2][0] == '0')
	{
		free_double_array(splits);
		return(-1);
	}
	set->width = ft_atoi(splits[1]);
	set->height = ft_atoi(splits[2]);
	if (ft_strlen(splits[1]) >= 5 || set->width > max_width)
		set->width = max_width;
	if (ft_strlen(splits[2]) >= 5 || set->height > max_height)
		set->height = max_height;
	free_double_array(splits);
	return (0);
}

int	check_overlap_and_init(char **checked_s, char **input_s)
{
	if (*checked_s == 0)
	{
		*checked_s = ft_strdup(input_s[1]);
		free_double_array(input_s);
		return (0);
	}
	free_double_array(input_s);
	return (-1);
}

int	get_texture(t_set *set, char **splits)
{
	if (split_len(splits) != 2)
	{
		free_double_array(splits);
		return(-1);
	}	
	if (ft_strcmp(splits[0], "NO") == 0)
		return (check_overlap_and_init(&set->north, splits));
	else if (ft_strcmp(splits[0], "SO") == 0)
		return (check_overlap_and_init(&set->south, splits));
	else if (ft_strcmp(splits[0], "WE") == 0)
		return (check_overlap_and_init(&set->west, splits));
	else if (ft_strcmp(splits[0], "EA") == 0)
		return (check_overlap_and_init(&set->east, splits));
	else if (ft_strcmp(splits[0], "S") == 0)
		return (check_overlap_and_init(&set->sprite_texture, splits));
	return (0); 
}

int		get_ceiling_or_floor(t_color *color, char **colors, char **splits)
{
	if ((color->red != -1 || color->green != -1 || color->blue != -1) ||\
	 (!(num_only(colors[0]) && num_only(colors[1]) && num_only(colors[2]))))
	{
		free(colors);
		free_double_array(splits);
		return (-1);
	}
	color->red = ft_atoi(colors[0]);
	color->green = ft_atoi(colors[1]);
	color->blue = ft_atoi(colors[2]);
	if (color->red > 255 || color->green > 255 || color->blue > 255)
	{
		free(colors);
		free_double_array(splits);
		return (-1);
	}
	free_double_array(colors);
	free_double_array(splits);
	return (0);
}

int		color_application(t_set *set, char **color, char **splits)
{
	if (ft_strcmp(splits[0],"F") == 0)
		return(get_ceiling_or_floor(&set->floor_color, color, splits));
	else if (ft_strcmp(splits[0],"C") == 0)
		return(get_ceiling_or_floor(&set->ceiling_color, color, splits));
	return (0);
}

int		get_color(t_set *set, char **splits)
{
	char **color;
	int		i;

	i = -1;
	if (split_len(splits) != 2)
	{
		free_double_array(splits);
		return(-1);
	}
	while(splits[1][++i])
	{
		if (splits[1][i] == ',' && splits[1][i + 1] == ',')
		{
			free_double_array(splits);
			return (-1);
		}
	}
	color = ft_split(splits[1],',');
	if (split_len(color) != 3)
	{
		free_double_array(splits);
		free_double_array(color);
		return(-1);
	}
	return (color_application(set, color, splits));
}

int		check_info(t_set *set,char **splits)
{
	if (ft_strcmp(*splits, "R") == 0)
		return (get_screen_size(set, splits));
	if (ft_strcmp(*splits, "SO") == 0)
		return (get_texture(set, splits));
	if (ft_strcmp(*splits, "NO") == 0)
		return (get_texture(set, splits));
	if (ft_strcmp(*splits, "WE") == 0)
		return (get_texture(set, splits));
	if (ft_strcmp(*splits, "EA") == 0)
		return (get_texture(set, splits));
	if (ft_strcmp(*splits, "S") == 0)
		return (get_texture(set, splits));
	if (ft_strcmp(*splits, "F") == 0)
		return (get_color(set, splits));
	if (ft_strcmp(*splits, "C") == 0)
		return (get_color(set, splits));
	else if (*splits[0] == '\0')
		return (0);
	return (1); 
}

int	parse_line(t_set *set ,char *line)
{
	char	**splits;
	int		i;

	i = 0;
	splits = ft_split(line, ' ');
	if (*splits == 0)	
	{
		free(splits);
		return (0);
	}
	else
		return (check_info(set, splits));
}

int	check_complete(t_set *set)
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

int	init_map(t_set *set, t_list *lst)
{
	int i;
	int j;

	i = 0;
	set->map_height = ft_lstsize(lst);
	set->map = (char **)malloc(sizeof(char *) * (set->map_height + 1));
	if (set->map == 0)
		return exit_error(set);
	set->map_width = get_max_line_size(lst);
	while (lst)
	{
		set->map[i] = (char *)malloc(sizeof(char) * (set->map_width + 1));
		if (set->map[i] == 0)
			return (exit_error(set));
		j = 0;
		while (j < set->map_width)
			set->map[i][j++] = ' ';
		set->map[i][set->map_width] = '\0';
		lst = lst->next;
		i++;
	}
	return (1);
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

int	fill_map(t_set *set, t_list *lst)
{
	int i;
	int j;
	char *line;
	int dir_count;

	i = -1;
	dir_count = 0;
	while (++i < set->map_height)
	{
		j = -1;
		line = (char *)lst->content;
		while (++j < (int)ft_strlen(line))
		{
			if (is_map_arg(line[j]) == -1)
				return (exit_error(set));
			set->map[i][j] = line[j];
			init_direction(set, i, j, &dir_count);
		}
		lst = lst->next;
	}
	ft_lstclear(&lst, &free);
	if (dir_count == 0 || dir_count > 1)
		return (exit_error(set));
	return (1);
}

int	check_valid_map(t_set *set)
{
	int i;
	int j;

	i = 0;
	while (i < set->map_height)
	{
		j = 0;
		while (j < set->map_width)
		{
			if (set->map[i][j] != ' ')
			{
				if (!up_test(set, i, j))
					return (exit_error(set));
				if (!down_test(set, i, j))
					return (exit_error(set));
				if (!left_test(set, i, j))
					return (exit_error(set));
				if (!rigth_test(set, i, j))
					return (exit_error(set));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_map(t_set *set, t_list *lst)
{
	if (!init_map(set, lst))
		return (exit_error(set));
	if (!fill_map(set, lst))
		return (exit_error(set));
	ft_lstclear(&lst, free);
	if (!check_valid_map(set))
		return (exit_error(set));
	return (1);
}

int	read_map(t_set *set, char *line)
{
	t_list	*lst;
	int		begun;

	begun = 0;
	set->map_height = 0;
	set->map_width = 0;
	while (get_next_line(set->fd, &line) > 0)
	{
		if (*line != 0)
		{
			ft_lstadd_back(&lst, ft_lstnew(line));
			begun = 1;
		}
		else if (begun ==1 && *line == 0)
			ft_lstadd_back(&lst, ft_lstnew(line));
		else
			free(line);
	}
	if (*line != 0)
		ft_lstadd_back(&lst, ft_lstnew(line));
	parse_map(set, lst);
	return (1);
}

int		check_init(t_set *set)
{
	if (!set->width || !set->height || !set->map_width ||\
		!set->map_height || !set->north ||\
		!set->south || !set->west ||\
		!set->east  ||!set->sprite_texture)
		return (exit_error(set));
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

int		parse_cub(t_set *set, char *path)
{
	char	*line;

	init_info(set, &set->floor_color, &set->ceiling_color);
	set->fd = open(path, O_RDONLY);
	while (get_next_line(set->fd, &line) > 0)
	{
		if ((parse_line(set, line)) == -1)
		{
			close(set->fd);
			return (exit_error(set));
		}
		free(line);
		line = 0;
		if (check_complete(set) == 1)
			break;
	}
	if (!check_complete(set))
		return (exit_error(set));
	if (!read_map(set, line))
		return (exit_error(set));
	if (!check_init(set))
		return (exit_error(set));
	if (!set_sprite(set))
		return (exit_error(set));
	return (1);
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

int		init_texture(t_set *set)
{
	int	i;
	int	j;

	if (!(set->texture = (int **)malloc(sizeof(int *) * 5)))
		return (exit_error(set));
	i = 0;
	while (i < 5)
	{
		if (!(set->texture[i] =\
				(int *)malloc(sizeof(int) * (TEXTURE_HEIGHT * TEXTURE_WIDTH))))
			return (exit_error(set));
		j = 0;
		while (j < TEXTURE_HEIGHT * TEXTURE_WIDTH)
		{
			set->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (1);
}

void	load_image(t_set *set, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(\
					set->mlx, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(\
					img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] =\
					img->data[img->width * y + x];
			x++;
		}
		y++;
	}
}

void	check_texture_file_exists(t_set *set)
{
	int	we;
	int	ea;
	int	so;
	int	no;
	int	sp;

	if ((we = open(set->west, O_RDONLY)) == -1)
		exit_error(set);
	if ((ea = open(set->east, O_RDONLY)) == -1)
		exit_error(set);
	if ((so = open(set->south, O_RDONLY)) == -1)
		exit_error(set);
	if ((no = open(set->north, O_RDONLY)) == -1)
		exit_error(set);
	if ((sp = open(set->sprite_texture, O_RDONLY)) == -1)
		exit_error(set);
	close(we);
	close(so);
	close(ea);
	close(no);
	close(sp);
}

void	load_texture(t_set *set)
{
	check_texture_file_exists(set);
	load_image(set, set->texture[3], set->north, &set->img);
	load_image(set, set->texture[2], set->south, &set->img);
	load_image(set, set->texture[1], set->west, &set->img);
	load_image(set, set->texture[0], set->east, &set->img);
	load_image(set, set->texture[4], set->sprite_texture, &set->img);
	ft_free(set->north);
	ft_free(set->south);
	ft_free(set->west);
	ft_free(set->east);
	ft_free(set->sprite_texture);
}

int		set_information(t_set *set, char *path)
{
	init_player(&set->player);
	if (!parse_cub(set, path))
		return (exit_error(set));
	init_player_direction(set);
	set->mlx = mlx_init();
	if (!init_texture(set))
		return (exit_error(set));
	load_texture(set);
	set->ray = (t_ray *)malloc(sizeof(t_ray) * set->width);
	set->img.img = mlx_new_image(set->mlx, set->width, set->height);
	set->img.data = (int *)mlx_get_data_addr(\
		set->img.img, &set->img.bpp, &set->img.size_l, &set->img.endian);
	return (1);
}

int		main(int argc, char **argv)
{
	t_set	set;

	if (argc < 2 || !check_extension(argv[1], ".cub"))
		return (exit_error(&set));
	else if (!set_information(&set, argv[1]))
		return (exit_error(&set));
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
		return (process_bmp(&set));
	else
		process_program(&set);
	return (0);
}