#include "cub3d.h"

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

int	check_overlap_and_init_texture(char **checked_s, char **input_s)
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
		return (check_overlap_and_init_texture(&set->north, splits));
	else if (ft_strcmp(splits[0], "SO") == 0)
		return (check_overlap_and_init_texture(&set->south, splits));
	else if (ft_strcmp(splits[0], "WE") == 0)
		return (check_overlap_and_init_texture(&set->west, splits));
	else if (ft_strcmp(splits[0], "EA") == 0)
		return (check_overlap_and_init_texture(&set->east, splits));
	else if (ft_strcmp(splits[0], "S") == 0)
		return (check_overlap_and_init_texture(&set->sprite_texture, splits));
	return (0); 
}
