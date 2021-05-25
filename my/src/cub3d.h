#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <float.h>
#include <fcntl.h>
#include <errno.h>
#include "../library/libft/libft.h"
#include "../library/libft/get_next_line.h"
#include "../library/mlx/mlx.h"
#include "../library/mlx/minilibx_opengl_custom-master/mlx_custom.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_RELEASE		3
#define X_EVENT_KEY_EXIT		17

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