# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:37:21 by ugdaniel          #+#    #+#              #
#    Updated: 2024/05/23 15:48:34 by ugdaniel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = clang
CFLAGS = -Wall -Wextra -Werror

SRCS  = srcs/main.c \
		srcs/directory.c \
		srcs/entry.c \
		srcs/file.c \
		srcs/list.c \
		srcs/parser.c \
		srcs/time.c \
		srcs/ft_xmalloc.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE = -I include -I $(LIBFT_DIR)/include

LIBS = $(LIBFT)

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

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Linking $(NAME)$(__default)"
	$(SILENT)$(CC) -o $@ $^ $(LIBS)
	@echo "$(__green)Successfully built $(NAME)$(__default)"

$(LIBFT):
	@echo "$(__default)Compiling Libft"
	$(SILENT)make --no-print-directory -C $(LIBFT_DIR)
	$(SILENT)make --no-print-directory -C $(LIBFT_DIR) clean

clean_libft:
	$(SILENT)make --no-print-directory verbose=$(verbose) fclean -C $(LIBFT_DIR)

.c.o:
	@echo "$(__default)Compiling $<"
	$(SILENT)mkdir -p $(dir $@)
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(SILENT)rm -f $(OBJS)

fclean: clean
	$(SILENT)rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re