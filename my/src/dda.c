#include "cub3d.h"

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