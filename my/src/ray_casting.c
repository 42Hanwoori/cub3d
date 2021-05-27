#include "cub3d.h"

void	init_ray(t_ray *ray, double ray_angle)
{
	ray->ray_angle = normalize_angle(ray_angle);
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->wall_distance = 0;
	ray->ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->ray_facing_up = !ray->ray_facing_down;
	ray->ray_facing_right = ray->ray_angle < 0.5 * PI ||
	ray->ray_angle > 1.5 * PI;
	ray->ray_facing_left = !ray->ray_facing_right;
	ray->was_hit_vertical = 0;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->found_horz_wall_hit = 0;
	ray->found_vert_wall_hit = 0;
	ray->h_dist = 0;
	ray->v_dist = 0;
}

void	ray_casting(t_set *set)
{
	float	ray_angle;
	int		ray_count;

	ray_count = -1;
	ray_angle = set->player.player_angle - (set->fov / 2);
	while (++ray_count < set->width)
	{
		init_ray(&set->ray[ray_count], ray_angle);
		ray_cal_dda(set, &set->ray[ray_count], 0, 0);
		ray_angle += set->fov / (set->width - 1);
	}
}
