#include "cub3d.h"

void			ft_file_header(t_set *set, int fd)
{
	int						filesize;
	int						padding;
	static unsigned char	fileheader[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	padding = (4 - (set->width * 3) % 4) % 4;
	filesize = 54 + (3 * set->width + padding) * set->height;
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	fileheader[2] = (unsigned char)(filesize);
	fileheader[3] = (unsigned char)(filesize >> 8);
	fileheader[4] = (unsigned char)(filesize >> 16);
	fileheader[5] = (unsigned char)(filesize >> 24);
	fileheader[10] = (unsigned char)(54);
	write(fd, fileheader, 14);
}

void			ft_image_header(t_set *set, int fd)
{
	static unsigned char	infoheader[] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	infoheader[0] = (unsigned char)(40);
	infoheader[4] = (unsigned char)(set->width);
	infoheader[5] = (unsigned char)(set->width >> 8);
	infoheader[6] = (unsigned char)(set->width >> 16);
	infoheader[7] = (unsigned char)(set->width >> 24);
	infoheader[8] = (unsigned char)(set->height);
	infoheader[9] = (unsigned char)(set->height >> 8);
	infoheader[10] = (unsigned char)(set->height >> 16);
	infoheader[11] = (unsigned char)(set->height >> 24);
	infoheader[12] = (unsigned char)(1);
	infoheader[14] = (unsigned char)(24);
	write(fd, infoheader, 40);
}

void			ft_save_buffer(t_set *set, int fd)
{
	int						i;
	int						j;
	int						padding;
	static unsigned char	zero[3] = { 0, 0, 0};

	padding = (4 - (set->width * 3) % 4) % 4;
	i = set->height;
	while (i > 0)
	{
		i--;
		j = 0;
		while (j < set->width)
		{
			write(fd, &set->img.data[i * set->width + j], 3);
			j++;
		}
		if (padding > 0)
			write(fd, &zero, padding);
	}
}

int				process_bmp(t_set *set)
{
	int	fd;

	ray_casting(set);
	draw_3d_wall(set);
	draw_sprite(set);
	fd = open("output.bmp"
					, O_WRONLY | O_TRUNC | O_CREAT, 0744);
	ft_file_header(set, fd);
	ft_image_header(set, fd);
	ft_save_buffer(set, fd);
	return (0);
}
