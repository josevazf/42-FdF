/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/31 15:57:20 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define ERROR 1
# define SUCCESS 0

# define WIN_W 1600
# define WIN_H 900

# define CLR_RED			0xFF0000
# define CLR_GREEN			0x00FF00
# define CLR_BLUE			0x0000FF
# define CLR_WHITE			0xFFFFFF
# define CLR_BLACK			0x000000
# define CLR_NEON			0xFF10F0

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
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		clr;
	t_color	rgb;
}	t_point;

typedef struct s_data
{
	int		w;
	int		h;
	int		z_max;
	int		z_min;
	double	angle_z;
	int		z_range;
	float	z_ratio;
	float	scale_ratio;
	int		trs_x;
	int		trs_y;
	int		c_pos_x;
	int		c_pos_y;
	int		err;
	int		x1;
	int		y1;
	double	z_angle;
	int		flag_col;
	int		flag_h;
	int		flag_top;
	t_point	**map;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	char	*map_name;
}	t_data;

// fdf_main.c
void	standard_screen(t_data *data);
void	set_vars(t_data *data);
int		key_events(int key, t_data *data);
void	menu_controls(t_data *data);

// fdf_map.c
void	process_map(char *file_name, t_data *data);
void	get_dimensions(char *file_name, t_data *data);
void	fill_map(t_point *map, char *line, t_data *data);
void	create_map(t_data *data);
void	get_maxmin(t_data *data, int val);

// fdf_draw.c
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_lines(t_point *p1, t_point *p2, t_data *data, int i);
void	draw_map(t_data *data);
void	vertical_lines(t_data *data);
void	horizontal_lines(t_data *data);

// fdf_color.c
void	hex_to_rgb(int hex_color, t_point *data);
int		get_pnt_color(t_point *p1, t_point *p2, float pos, int len);
void	make_gradient(t_data *data, int clr1, int clr2);
int		terrain_fade(int z);
void	set_terrain(t_data *data);

// fdf_transf1.c
void	set_coordinates(t_data *data);
void	scale_map(t_data *data, double factor);
void	translate_center(t_data *data, int i, int j);
void	iso_transfer(t_data *data, double angle, float ratio);
void	fit_to_window(t_data *data, double angle);

// fdf_transf2.c
void	get_map_center(t_data *data);
void	rotate_z(t_data *data, double angle, int i, int j);
void	top_view(t_data *data);
void	clean_screen(t_data *data);

// fdf_events1.c
int		esc_key(t_data *data);
int		scale_height(t_data *data, int key);
void	translate_map(t_data *data, int key);
void	zoom_map(t_data *data, int key);
void	rotate_map(t_data *data, int key);

// fdf_events2.c
void	change_colors(t_data *data, int key);

// fdf_utils.c
float	get_average(t_data *data, int t);
float	get_pnt_position(float z, t_data *data);
int		get_slope(int p1, int p2);
void	get_zratio(t_data *data);
double	get_rad(double deg);

// fdf_error.c
int		map_error(void);
int		args_error(void);
int		fd_error(int fd);
int		malloc_error(void *input);
void	ft_free_map(t_point **matrix);

#endif
