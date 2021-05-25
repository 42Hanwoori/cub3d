/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 21:31:58 by ji-park           #+#    #+#             */
/*   Updated: 2021/03/15 21:55:01 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(\
					info->mlx, path, &img->width, &img->height);
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

void	check_texture_file_exists(t_info *info)
{
	int we;
	int ea;
	int so;
	int no;
	int sp;

	if ((we = open(info->west, O_RDONLY)) == -1)
		exit_error(info);
	if ((ea = open(info->east, O_RDONLY)) == -1)
		exit_error(info);
	if ((so = open(info->south, O_RDONLY)) == -1)
		exit_error(info);
	if ((no = open(info->north, O_RDONLY)) == -1)
		exit_error(info);
	if ((sp = open(info->sprite_texture, O_RDONLY)) == -1)
		exit_error(info);
	close(we);
	close(so);
	close(ea);
	close(no);
	close(sp);
}

void	load_texture(t_info *info)
{
	t_img	img;

	check_texture_file_exists(info);
	load_image(info, info->texture[3], info->north, &img);
	load_image(info, info->texture[2], info->south, &img);
	load_image(info, info->texture[0], info->west, &img);
	load_image(info, info->texture[1], info->east, &img);
	load_image(info, info->texture[4], info->sprite_texture, &img);
	ft_free(info->north);
	ft_free(info->south);
	ft_free(info->west);
	ft_free(info->east);
	ft_free(info->sprite_texture);
}
