# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 10:36:01 by jrocha-v          #+#    #+#              #
#    Updated: 2023/10/31 16:01:28 by jrocha-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fdf

SRCS_DIR		= src

OBJS_DIR		= objs

INCLUDES		= includes
LIBFT			= ./libs/libft/libft.a
LIBFT_DIR		= ./libs/libft
LIBMLX			= ./libs/minilibx-linux/libmlx.a
LIBMLX_DIR		= ./libs/minilibx-linux

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
MLX_FLAGS		= -lmlx_Linux -lXext -lX11 -lm -lbsd

MK_FLAG			= --no-print-directory
RM				= rm -rf

SRCS		= fdf_main.c \
				  fdf_events1.c \
				  fdf_events2.c \
				  fdf_map.c \
				  fdf_draw.c \
				  fdf_color.c \
				  fdf_transf1.c \
				  fdf_transf2.c \
				  fdf_utils.c \
				  fdf_error.c

# Substitute .c with .o 
OBJS			= $(SRCS:%.c=$(OBJS_DIR)/%.o)

#default target
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBMLX_DIR) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	echo "Finished!"

#create .o files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@

$(LIBFT):
	echo "Compiling necessary libs..."
	$(MAKE) $(MK_FLAG) -C $(LIBFT_DIR)

$(LIBMLX):
	echo "Compiling necessary libs..."
	$(MAKE) $(MK_FLAG) -C $(LIBMLX_DIR)

#remove .o files
clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(LIBMLX_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(LIBMLX)

#reset - remove and recompile
re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
.SILENT:
