#0. 앞으로 여러가지 파일을 작성해서 cub3D세계를 구축한다. 이때 파일에서 mlx라이브러리와 libft라이브러리를 가져와
#자유롭게 그 함수를 끌어다가 쓸것이다. 그러므로 함께 컴파일 되도록 makefile을 작성한다.
##1. 소스파일들을 오브젝트 파일로 컴파일한다.
##2. libft 정적 라이브러리로 생성한다.
##3. mlx 동적 라이브러리 생성한다.
##4. 위 세개를 엮어(링크하여) cub3D 실행파일 생성!

#makefile은 변수와 디펜던시, 그리고 커맨드로 이루어져 있다. 읽는 순서는 위에서 아래로 순차적으로 읽어나가는데,
#여기서 먼저 선언되는 변수들은 넘어가고 처음으로 출현하는 디펜던시의 타겟 즉 all을 생성한다.
#all은 Name 즉 최종 타깃인 cub3D 이므로 타깃이 의존하는 디펜던시들(재료)을 읽고, 없다면 찾거나 생성한다.
#(※만약 )

NAME = cub3D


CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -f

LIB_FLAG = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L $(LIBFT_DIR) -lft
MLX = libmlx.a
MLX_DIR = ./library/mlx
LIBFT = libft.a
LIBFT_DIR = ./library/Libft
INCLUDE = -I./include -I./library/libft -I./library/mlx

SRCS_FILE = main.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILE))

SRCS_DIR = ./src#???????????순서가 왜 위에꺼보다 앞서지 않아도 컴파일이 되나? 무엇이 먼저 나와야하나?

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
