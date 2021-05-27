#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h>
# include <float.h>
# include <fcntl.h>
# include <errno.h>
# include "../library/libft/libft.h"
# include "../library/libft/get_next_line.h"
# include "../library/mlx/mlx.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC				53
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define PI 					3.1415926535897
# define TILE_SIZE 				64
# define F_MAX					FLT_MAX
# define TEXTURE_WIDTH			64
# define TEXTURE_HEIGHT			64

typedef struct					s_img
{
	void						*img;
	int							*data;

	int							width;
	int							height;
	int							size_l;
	int							bpp;
	int							endian;
}								t_img;

typedef struct					s_ray
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
	double						wall_hit_x;
	double						wall_hit_y;
	double						wall_distance;
	int							found_horz_wall_hit;
	int							found_vert_wall_hit;
	int							was_hit_vertical;
}								t_ray;

typedef struct					s_wall
{
	float						corr_wall_dist;
	double						dist_to_win;
	int							wall_height_in_win;
	int							wall_strip_y_top;
	int							wall_strip_y_bottom;
	float						proj_wall_height;
}								t_wall;

typedef struct					s_player
{
	float						x;
	float						y;
	float						rad;
	float						player_angle;
	int							right_move;
	int							left_move;
	int							walk_dir;
	int							turn_dir;
	float						walk_speed;
	float						turn_speed;
}								t_player;

typedef struct					s_color
{
	int							red;
	int							green;
	int							blue;
}								t_color;

typedef struct					s_sprite
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
	int							tex_offset_x;
	int							tex_offset_y;
	double						screen_pos_x;
	int							visible;
	int							texture;
}								t_sprite;

typedef struct					s_set
{
	void						*mlx;
	void						*win;
	t_img						img;

	t_player					player;
	t_ray						*ray;
	t_wall						wall;
	t_sprite					*sprite;
	double						fov;
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

int								is_map_arg(char c);
int								check_extension(char *s, char *s_ext);
float							normalize_angle(float angle);
double							dbt(double x1, double y1,\
								double x2, double y2);
void							clear_window(t_set *set);

int								cal_floor_ceiling_color(t_color color);
int								num_only(char *s);
int								split_len(char **split);
void							ft_free(void *s);
int								ft_close(void);

void							free_double_array(char **s);
int								exit_error(t_set *set, char *s);
int								ft_strcmp(char *str1, char *str2);
void							ft_putstr(char *s);

int								inside_wall(t_set *set, double next_x, \
								double next_y);
void							wall_init(t_set *set, t_wall *wall, int i);
int								texture_by_wall_dir(t_set *set, int x, \
								int y, int i);
void							draw_strip_in_wall(t_set *set, t_wall *wall,\
								int *y, int i);
void							draw_3d_wall(t_set *set);

void							draw_sprite_by_stripe(t_set *set, \
								t_sprite *sprite, int x, int y);
void							draw_visible_sprites(t_set *set);
void							check_visible_sprites(t_set *set, int i);
void							rearrange_sprites_by_dist(t_set *set, \
								t_sprite *sprite);
void							draw_sprite(t_set *set);

void							set_sprite_position(t_set *set, \
								t_sprite *sprite);

void							init_ray(t_ray *ray, double ray_angle);
void							ray_casting(t_set *set);

int								get_screen_size(t_set *set, char **splits);
int								check_info(t_set *set, char **splits);
int								parse_line(t_set *set, char *line);
int								parse_cub(t_set *set, char *path);
int								set_information(t_set *set, char *path);

int								get_ceiling_or_floor(t_color *color, \
								char **colors, char **splits);
int								color_application(t_set *set, char **color, \
								char **splits);
int								get_color(t_set *set, char **splits);
int								check_overlap_and_init_texture\
								(char **checked_s, char **input_s);
int								get_texture(t_set *set, char **splits);

int								check_complete(t_set *set);
int								get_max_line_size(t_list *lst);
int								check_init(t_set *set);
int								set_sprite(t_set *set);

int								init_texture(t_set *set);
void							load_image(t_set *set, int *texture, \
								char *path, t_img *img);
void							check_texture_file_exists(t_set *set);
void							load_texture(t_set *set);

int								init_map(t_set *set, t_list *lst);
int								fill_map(t_set *set, t_list *lst);
int								check_valid_map(t_set *set);
int								parse_map(t_set *set, t_list *lst);
int								read_map(t_set *set, char *line);

int								up_test(t_set *set, int i, int j);
int								down_test(t_set *set, int i, int j);
int								left_test(t_set *set, int i, int j);
int								rigth_test(t_set *set, int i, int j);
int								is_dir(char c);

int								key_release(int key_code, t_player *player);
int								key_press(int key_code, t_set *set);
void							update_player(t_set *set, t_player *player);
int								main_loop(t_set *set);
int								process_program(t_set *set);

void							check_ray_hit_horz_set(t_set *set, t_ray *ray);
void							check_ray_hit_horz(t_set *set, t_ray *ray, \
								double *wall_horz_x, double *wall_horz_y);
void							check_ray_hit_vert_set(t_set *set, t_ray *ray);
void							check_ray_hit_vert(t_set *set, t_ray *ray, \
								double *wall_vert_x, double *wall_vert_y);
void							ray_cal_dda(t_set *set, t_ray *ray,
												double horz_x, double horz_y);

void							set_int_in_char(unsigned char *start, \
								int value);
void							write_bmp_header(t_set *set, int fd, int size);
void							write_data(t_set *set, int fd);
int								save_bmp(t_set *set);
int								process_bmp(t_set *set);

void							init_player(t_player *player);
void							init_info(t_set *set, t_color *color, \
								t_color *color2);
void							init_direction(t_set *set, int i, int j, \
								int *dir_count);
void							init_player_direction(t_set *set);

#endif
