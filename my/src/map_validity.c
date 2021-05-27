#include "cub3d.h"

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
