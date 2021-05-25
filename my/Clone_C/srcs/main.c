/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-park <ji-park@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:42:20 by ji-park           #+#    #+#             */
/*   Updated: 2021/03/18 04:08:12 by ji-park          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int set_info (t_info *info, char *path)
{
    init_player(&info->player);
    if (!parse_cub(info, path))
        return (exit_error(info));
    init_player_direction(info);
    info->mlx = mlx_init();
    if (!init_buffer(info))
        return (exit_error(info));
    if (!init_texture(info))
		return (exit_error(info));
	load_texture(info);
    info->img.img = mlx_new_image(info->mlx, info->width, info->height);
    info->img.data = (int *)mlx_get_data_addr(\
		info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
    return (1);
}

int     process_option(t_info *info, int option)
{
	if (option == 1)
	{
		raycasting(info);
		sprite_raycasting(info, &info->player);
		if (!save_bmp(info))
			return (exit_error(info));
		ft_exit(0);
	}
	else
	{
		info->win =\
			mlx_new_window(info->mlx, info->width, info->height, "someTitle");
		mlx_hook(info->win, X_EVENT_KEY_PRESS, 0, key_press, info);
		mlx_hook(info->win, X_EVENT_KEY_EXIT, 0, ft_exit, 0);
		mlx_loop_hook(info->mlx, main_loop, info);
		mlx_loop(info->mlx);
	}
	return (1);
}

void print_info(t_info info)
{
    printf("width : %d\n",info.width);
    printf("height : %d\n",info.height);
    printf("east : %s\n",info.east);
    printf("north : %s\n",info.north);
    printf("south : %s\n",info.south);
    printf("west : %s\n",info.west);
    printf("floor_color R : %d\n",info.floor_color.red);
    printf("floor_color G : %d\n",info.floor_color.green);
    printf("floor_color B : %d\n",info.floor_color.blue);
    printf("ceiling_color R : %d\n",info.ceiling_color.red);
    printf("ceiling_color G : %d\n",info.ceiling_color.green);
    printf("ceiling_color B : %d\n",info.ceiling_color.blue);
    printf("dir : %d\n",info.dir);
    printf("sprite : %d\n",info.num_sprite);
}

int main(int argc, char **argv)
{
    t_info info;
    int     option;
    int     check_map_name_v_fd;

    option = (argc >= 2 && (ft_strncmp(argv[1], "--save", 6) == 0)) ? 1 : 0;
    if (argc < option + 2)
        return (exit_error(&info));
    if ((check_map_name_v_fd = open(argv[1], O_RDONLY)) == -1)
        return (exit_error(&info));
    if (set_info(&info, argv[1]) == -1)
        return (exit_error(&info));
    print_info(info);
    if (!process_option(&info, option))
        return (exit_error(&info));
    return (0);
}