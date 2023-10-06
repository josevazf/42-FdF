/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/06 12:26:26 by jrocha-v         ###   ########.fr       */
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

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

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

typedef struct s_data
{
    int     height;
    int     width;
    int     **alt_matrix;
    
    void    *mlx_ptr;
    void    *win_ptr;
	t_img	img;
}   t_init;

// fdf_main.c

// fdf_read_map.c
void	read_file(char *file_name, t_init *data);
int		get_height(char *file_name);
int		get_width(char *file_name);
void	fill_matrix(int *altitude, char *line);
void	create_matrix(t_init *data);

// fdf_draw.c
void	ft_pixel_put(t_img *img, int x, int y, int color);
void	color_screen(t_init *data, int color);

// fdf_events.c
int		esc_key(int key, t_init *data);

// fdf_error.c
int		args_error(void);
int		fd_error(int fd);
int		malloc_error(void* input);

#endif
