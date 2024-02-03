# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:37:21 by ugdaniel          #+#    #+#              #
#    Updated: 2024/02/03 12:31:55 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls

SRCS 	= srcs/main.c
OBJS	= $(SRCS:.c=.o)
INCLUDE	= -I include
INCLUDE	+= -I libft/include

CC		= clang
CFLAGS	= -Wall -Wextra -Werror
LIBS	= libft/libft.a

__default = \033[39m
__green = \033[92m
__magenta = \033[95m
__yellow = \033[33m
__blue = \033[34m
__gray = \033[37m
__red = \033[91m
__cyan = \033[96m

ifndef verbose
  SILENT = @
endif

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)$(__default)"
	$(SILENT)$(CC) -o $@ $^ $(LIBS)
	@echo "$(__green)Successfully built $(NAME)$(__default)"

.c.o:
	@echo "Compiling $<$(__default)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re