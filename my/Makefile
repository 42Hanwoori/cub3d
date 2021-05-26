NAME = cub3D


CC = gcc
CFLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror
RM = rm -f

LIB_FLAG = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L $(LIBFT_DIR) -lft
MLX = libmlx.a
MLX_DIR = ./library/mlx
LIBFT = libft.a
LIBFT_DIR = ./library/libft
INCLUDE = -I./include -I./library/libft -I./library/mlx

SRCS_FILE = main.c utils1.c utils2.c utils3.c wall.c sprite1.c sprite2.c ray_casting.c\
			parse1.c parse2.c parse3.c parse_load_texture.c parse_load_map.c map_validity.c\
			loop.c dda.c bmp.c init.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILE))

SRCS_DIR = ./src

OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILE:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS) $(MLX_DIR)/$(MLX) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(CFLAGS) $(LIB_FLAG) $(OBJS) $(INCLUDE) -o $@

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_DIR)/$(LIBFT) :
	@$(MAKE) all -C $(LIBFT_DIR)
#makefile이 실행되는 곳이 아닌 곳에서 재귀적인 make를 실행할 경우 변수를 선언할때
#디렉토리(위치)를 함께 입력해야 한다. 변수선언 뿐만 아니라 -C 옵션으로 make가 실행되는 위치도 입력해야 한다.

$(MLX_DIR)/$(MLX) : 
	@$(MAKE) all -C $(MLX_DIR)

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
#c파일이 컴파일될 때 참고하는 헤더파일이 같은 디렉토리에 없다면 -I./include 옵션으로 위치를 지정해 주어야함.

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean;
	@$(RM) $(SRCS_DIR)/*.o

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean;
	@$(MAKE) -C $(MLX_DIR) clean;
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
