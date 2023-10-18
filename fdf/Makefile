# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 10:36:01 by jrocha-v          #+#    #+#              #
#    Updated: 2023/10/18 17:15:06 by jrocha-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fdf

SRCS_DIR		= src/mandatory
SRCS_BONUS_DIR	= src/bonus

OBJS_DIR		= objs

INCLUDES		= includes
LIBFT			= ./libft/libft.a
LIBFT_DIR		= ./libft
LIBMLX			= ./minilibx-linux/libmlx.a
LIBMLX_DIR		= ./minilibx-linux

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
MLX_FLAGS		= -lmlx_Linux -lXext -lX11 -lm -lbsd

#gcc program.c -Lminilibx-linux -lmlx_Linux -o process -lX11 -lXext

MK_FLAG			= --no-print-directory
RM				= rm -rf

SRCS			= fdf_main.c \
				  fdf_events.c \
				  fdf_map.c \
				  fdf_draw.c \
				  fdf_color.c \
				  fdf_transform.c \
				  fdf_utils.c \
				  fdf_error.c

SRCS_BONUS		= fdf_main_bonus.c \
				  fdf_events_bonus.c \
				  fdf_map_bonus.c \
				  fdf_draw_bonus.c \
				  fdf_color_bonus.c \
				  fdf_transform_bonus.c \
				  fdf_utils_bonus.c \
				  fdf_error_bonus.c

# Substitute .c with .o 
OBJS			= $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS		= $(SRCS_BONUS:%.c=$(OBJS_DIR)/%.o)

#default target
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBMLX_DIR) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	echo "Finished!"

bonus: $(OBJS_BONUS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBMLX_DIR) $(MLX_FLAGS) $(LIBFT) -o \
	$(NAME)
	echo "Finished!"

#create .o fies
# $< first prerequisite aka .c; $@ output/target file aka .o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_BONUS_DIR)/%.c
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

#reset environment - remove everything and recompile
re: fclean
	$(MAKE) all

#targets declared as .PHONY will force the command even if there is a subdirectory or file with it's name
.PHONY: all clean fclean re
.SILENT: