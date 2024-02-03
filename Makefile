# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:37:21 by ugdaniel          #+#    #+#              #
#    Updated: 2024/02/03 10:37:54 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls

SRCS 	= srcs/main.c
OBJS	= $(SRCS:.c=.o)
INCLUDE	= -I include

CC		= clang
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) ready!"

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(DEFAULT)OK"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re