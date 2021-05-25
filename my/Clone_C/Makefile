NAME = cub3D

LIBFT = ./libft/libft.a

CC = gcc
INCS = -I./includes -I./libft -I./mlx
INCLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Llibft -lft
CFLAGS = -Wall -Werror -Wextra -g $(INCS)

LIBFT = ./libft

SRCS = main.c \
		parse_before_map.c \
		parse_before_map2.c \
		init.c \
		utils.c \
		get_next_line.c \
		get_next_line_utils.c\
		parse_check_map.c \
		check_map_validity.c \
		sprite_utils.c \
		key_press_event.c \
		load_image_texture.c \
		free_exit.c \
		raycasting_utils.c \
		main_loop_hook.c \
		cast_floor_ceiling.c \
		draw.c \
		get_wall_info.c \
		sprite_utils2.c \
		save_bmp_files.c

SRCS := $(addprefix ./srcs/, $(SRCS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT) all
	$(MAKE) -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(INCLIB)

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: test bonus all clean fclean re