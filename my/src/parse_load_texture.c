#include    "cub3d.h"

int		init_texture(t_set *set)
{
	int	i;
	int	j;

	if (!(set->texture = (int **)malloc(sizeof(int *) * 5)))
		return (exit_error(set));
	i = 0;
	while (i < 5)
	{
		if (!(set->texture[i] =\
				(int *)malloc(sizeof(int) * (TEXTURE_HEIGHT * TEXTURE_WIDTH))))
			return (exit_error(set));
		j = 0;
		while (j < TEXTURE_HEIGHT * TEXTURE_WIDTH)
		{
			set->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (1);
}

void	load_image(t_set *set, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(\
					set->mlx, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(\
					img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] =\
					img->data[img->width * y + x];
			x++;
		}
		y++;
	}
}

void	check_texture_file_exists(t_set *set)
{
	int	we;
	int	ea;
	int	so;
	int	no;
	int	sp;

	if ((we = open(set->west, O_RDONLY)) == -1)
		exit_error(set);
	if ((ea = open(set->east, O_RDONLY)) == -1)
		exit_error(set);
	if ((so = open(set->south, O_RDONLY)) == -1)
		exit_error(set);
	if ((no = open(set->north, O_RDONLY)) == -1)
		exit_error(set);
	if ((sp = open(set->sprite_texture, O_RDONLY)) == -1)
		exit_error(set);
	close(we);
	close(so);
	close(ea);
	close(no);
	close(sp);
}

void	load_texture(t_set *set)
{
	check_texture_file_exists(set);
	load_image(set, set->texture[3], set->north, &set->img);
	load_image(set, set->texture[2], set->south, &set->img);
	load_image(set, set->texture[1], set->west, &set->img);
	load_image(set, set->texture[0], set->east, &set->img);
	load_image(set, set->texture[4], set->sprite_texture, &set->img);
	ft_free(set->north);
	ft_free(set->south);
	ft_free(set->west);
	ft_free(set->east);
	ft_free(set->sprite_texture);
}
