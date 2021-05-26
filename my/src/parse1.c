#include "cub3d.h"

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