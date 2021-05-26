#include "cub3d.h"

void	free_double_array(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

int exit_error(t_set *set)
{
	ft_putstr("Error\n");
	if (set->fd)
		close(set->fd);
	exit(1);
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