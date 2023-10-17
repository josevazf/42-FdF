/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:31:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/17 08:30:04 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Put a pixel on the screen */
void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->mlx_pixel_addr)) = color;
}

/* Set the coordinates for the map points */
void	set_coordinates(t_data *data)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	spc_width = (WIN_W - 10 )/ (data->width - 1);
	spc_height = (WIN_H - 10)/ (data->height - 1);
	if ((spc_height * (data->height - 1) >= WIN_H) ||
		(spc_height * (data->width - 1) >= WIN_W))
		spacing = spc_width;
	else
		spacing = spc_height;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			data->map[i][j].x = 10 + (j * spacing);
			data->map[i][j].y = 10 + (i * spacing);
		}
	}
}

/* Fit isometric view to window */
void	fit_to_window(t_data *data)
{
	double ratio;

	ratio = 1;
	while ((data->map[data->height - 1][data->width - 1].y - 
		data->map[0][0].y >= WIN_H - 200))
	{
		if (data->map[data->height - 1][data->width - 1].y - data->map[0][0].y >= WIN_H - 200)
		{
			set_coordinates(data);
			scale_map(data, pow(0.9, ratio));
		}
		else if (data->map[data->height - 1][data->width - 1].y - data->map[0][0].y <= WIN_H / 2)
		{
			set_coordinates(data);
			scale_map(data, pow(1.1, ratio));
		}
	iso_transfer(data);
	center_map(data);
	ratio = ratio + 1;
	}
}

void	standard_screen(t_data *data)
{
	set_coordinates(data);
	iso_transfer(data);
	center_map(data);
	fit_to_window(data);
	draw_map(data);
}

/* Draw map by connectin points */
void    draw_map(t_data *data)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < data->height - 1)
	{
		j = -1;
		while (++j < (data->width))
			draw_lines(&data->map[i][j], &data->map[i + 1][j], data, i);
	}
	i = -1;
	j = -1;
	while (++j < data->width - 1)
	{
		i = -1;
		while (++i < data->height)
			draw_lines(&data->map[i][j], &data->map[i][j + 1], data, i);
	}
}	

/* Draw lines with gradient between p1 and p2 */
void    draw_lines(t_point *p1, t_point *p2, t_data *data, int i)
{
	int dx;
	int dy;
	int err;
	int x1;
	int y1;
	
	i = -1;
	x1 = p1->x;
	y1 = p1->y;
	dx = abs(p2->x - x1);
	dy = abs(p2->y - y1);
	err = dx - dy;
	while (++i < ft_int_max(dx, dy))
	{
		//ft_printf("%i\n", i);
		if (x1 > 0 && x1 < WIN_W - 5 && y1 > 0 && y1 < WIN_H - 5)
			put_pixel(&data->img, x1, y1, get_point_color(p1, p2, i, ft_int_max(dx, dy)));
		if (x1 == p2->x && y1 == p2->y)
			break ;
		if (2 * err > -dy) {
			err -= dy;
			x1 += get_slope(x1, p2->x);
		}
		if (2 * err < dx) {
			err += dx;
			y1 += get_slope(y1, p2->y);
		}
	}
}
