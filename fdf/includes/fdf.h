/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/18 16:19:33 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# define SUCCESS 0
# define ERROR 1

# define WIN_W 1600
# define WIN_H 900

# define CLR_RED			0xFF0000
# define CLR_GREEN			0x00FF00
# define CLR_BLUE			0x0000FF
# define CLR_WHITE			0xFFFFFF
# define CLR_BLACK			0x000000

# define CLR_TEXT			0xEAEAEA
# define CLR_MAIN_SCRN_BG	0x222222
# define CLR_SUB_SCRN_BG	0x1E1E1E
# define CLR_DISCO			0x9A1F6A
# define CLR_BRICK_RED		0xC2294E
# define CLR_FLAMINGO		0xEC4B27
# define CLR_JAFFA			0xEF8633
# define CLR_SAFFRON		0xF3AF3D

typedef struct s_img
{
	void	*mlx_img;
	char	*mlx_pixel_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_color
{
	int 	r;
	int		g;
	int		b;
}	t_color;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		clr;
	t_color	clrRGB;
}	t_point;

typedef struct s_data
{
    int     width;
    int     height;
	int		z_max;
	int		z_min;
	int		z_range;
	float	z_ratio;
	int 	err;
	int		x1;
	int		y1;
    t_point	**map;
    void    *mlx_ptr;
    void    *win_ptr;
	t_img	img;
}   t_data;

// fdf_main.c

// fdf_map.c
void	process_map(char *file_name, t_data *data);
void	get_dimensions(char *file_name, t_data *data);
void	fill_map(t_point *map, char *line, t_data *data);
void	create_map(t_data *data);

// fdf_draw.c
void	put_pixel(t_img *img, int x, int y, int color);
void	standard_screen(t_data *data);
void	set_coordinates(t_data *data);
void	draw_lines(t_point *p1, t_point *p2, t_data *data, int i);
void	draw_map(t_data *data);
void	vertical_lines(t_data *data);
void	horizontal_lines(t_data *data);


// fdf_color.c
void	hex_to_rgb(int hex_color, t_point *data);
int		create_rgb(int r, int g, int b);
int		get_pnt_color(t_point *p1, t_point *p2, int pos, int len);

// fdf_transform.c
void	scale_map(t_data *data, double factor);
void	center_map(t_data *data);
void	iso_transfer(t_data *data);
void	fit_to_window(t_data *data);

// fdf_events.c
void	ft_free_map(t_point **matrix);
int		esc_key(t_data *data);
void	c_key(t_data *data);
int		key_events(int key, t_data *data);

// fdf_utils.c
float	get_average(t_data *data, int t);
float	get_pnt_position(float z, t_data *data);
int     get_slope(int p1, int p2);
void	get_zratio(t_data *data);

// fdf_error.c
int		args_error(void);
int		fd_error(int fd);
int		malloc_error(void* input);

#endif
