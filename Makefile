# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:37:21 by ugdaniel          #+#    #+#              #
#    Updated: 2024/07/31 21:35:58 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ls

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -pedantic

SRCS 		=	srcs/main.c			\
				srcs/colors.c		\
				srcs/directory.c	\
				srcs/entry.c		\
				srcs/file.c			\
				srcs/list.c			\
				srcs/parser.c		\
				srcs/time.c			\
				srcs/ft_xmalloc.c

OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

LIBS		= $(LIBFT)
INCLUDE		= -I include -I $(LIBFT_DIR)/include

COLOR_DEFAULT	=	\033[39m
COLOR_GREEN		= 	\033[92m
COLOR_GREY		= 	\033[90m

ifndef verbose
  SILENT = @
  NO_PRINT_DIRECTORY = --no-print-directory
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(SILENT)$(CC) -o $@ $^ $(LIBS)
	@echo "$(COLOR_GREEN)Successfully built $(NAME)$(COLOR_DEFAULT)"

$(LIBFT):
	$(SILENT)$(MAKE) $(NO_PRINT_DIRECTORY) -C $(LIBFT_DIR)
	$(SILENT)$(MAKE) $(NO_PRINT_DIRECTORY) -C $(LIBFT_DIR) clean

clean_libft:
	$(SILENT)$(MAKE) $(NO_PRINT_DIRECTORY) verbose=$(verbose) fclean -C $(LIBFT_DIR)

.c.o:
	@echo "$(COLOR_GREY)Compiling $<...$(COLOR_DEFAULT)"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(SILENT)rm -f $(OBJS)

fclean: clean clean_libft
	$(SILENT)rm -f $(NAME)

re: fclean all

.PHONY: all clean clean_libft fclean re
