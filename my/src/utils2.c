#include "cub3d.h"

int		cal_floor_ceiling_color(t_color color)
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

int		split_len(char **split)
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
