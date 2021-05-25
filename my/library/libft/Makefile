# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: whan <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 10:46:22 by whan              #+#    #+#              #
#    Updated: 2021/04/23 16:17:05 by han_woori        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -f
AR = ar rc
SRCS = ft_atoi.c ft_isalpha.c ft_memccpy.c ft_memmove.c ft_strlcat.c ft_strnstr.c \
      ft_bzero.c ft_isascii.c ft_memchr.c ft_memset.c ft_strlcpy.c ft_strrchr.c \
      ft_isdigit.c ft_memcmp.c ft_strchr.c ft_strlen.c ft_tolower.c ft_substr.c\
      ft_strjoin.c ft_isalnum.c ft_isprint.c ft_memcpy.c ft_strncmp.c ft_toupper.c\
      ft_strdup.c ft_calloc.c ft_split.c ft_strtrim.c ft_itoa.c ft_strmapi.c\
      ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	  ft_lstadd_back.c ft_lstclear.c ft_lstnew.c ft_lstsize.c\
	  get_next_line.c get_next_line_utils.c


OBJS = $(SRCS:.c=.o)


all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

$(NAME) : $(OBJS)
	$(AR) $@ $^

re : fclean all

%.o : %.c
		$(CC) $(CFLAGS) -c $<

.PHONY : all clean fclean re
