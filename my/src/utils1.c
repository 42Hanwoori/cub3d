#include "cub3d.h"

int	is_map_arg(char c)
{
	if (is_dir(c) == 1 || c == ' ' ||
		(c >= '0' && c <= '2') ||
		c == '\n' || c == '\0')
		return (1);
	return (-1);
}

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

float	normalize_angle(float angle) 
{
	angle = fmodf(angle, (2 * PI));
	if (angle < 0)
		angle = (2 * PI) + angle;
	return angle;
}

double	distant_between_two(double x1, double y1, double x2, double y2)
{
	double	res;

	res =  sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return (res);
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