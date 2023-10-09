/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/09 16:23:10 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <unistd.h>
# include <stdlib.h>
# define SUCCESS 0
# define ERROR 1

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

# define ESC 65307

# define RED_PIXEL 0xFF0000

typedef struct s_img
{
	void	*mlx_img;
	char	*mlx_pixel_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_screen
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
}	t_screen;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		clr;
}	t_point;

typedef struct s_data
{
    int     height;
    int     width;
    t_point	**map;
	
    void    *mlx_ptr;
    void    *win_ptr;
	t_img	img;
}   t_data;

// fdf_main.c

// fdf_read_map.c
void	read_file(char *file_name, t_data *data);
int		get_height(char *file_name);
int		get_width(char *file_name);
void	fill_matrix(t_point *map, char *line);
void	create_matrix(t_data *data);

// fdf_draw.c
void	ft_pixel_put(t_img *img, int x, int y, int color);
void	color_screen(t_data *data, int color);
void	ft_set_coordinates(t_data *data);

// fdf_events.c
void	ft_free_map(t_point **matrix);
int		esc_key(int key, t_data *data);

// fdf_error.c
int		args_error(void);
int		fd_error(int fd);
int		malloc_error(void* input);

#endif
