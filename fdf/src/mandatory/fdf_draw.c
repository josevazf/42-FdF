/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:31:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/13 09:35:22 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->mlx_pixel_addr)) = color;
}

void	set_coordinates(t_data *data)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	spc_width = (WINDOW_WIDTH - 500) / (data->width - 1);
	spc_height = (WINDOW_HEIGHT - 500) / (data->height - 1);
	if (spc_height * (data->height - 1) >= WINDOW_HEIGHT)
		spacing = spc_width;
	else if (spc_height * (data->width - 1) >= WINDOW_WIDTH)
		spacing = spc_width;
	else
		spacing = spc_height;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
				data->map[i][j].x = 50 + (j * spacing);
				data->map[i][j].y = 50 + (i * spacing);
		}
	}
}

void	center_map(t_data *data)
{
	float	move_x;
	float	move_y;
	int		i;
	int		j;

	move_x = abs((float)data->map[0][0].x - (float)data->map[data->height-1][data->width-1].x) / 2;
	move_y = abs((float)data->map[0][0].y - (float)data->map[data->height-1][data->width-1].y) / 2;
	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
				data->map[i][j].x = data->map[i][j].x + move_x;
				data->map[i][j].y = data->map[i][j].y + move_y;
		}
	}
}

void	iso_transfer(t_data *data)
{
	float	_x;
	float	_y;
	float	_z;
	int		i;
	int		j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			_x = (float)data->map[i][j].x;
			_y = (float)data->map[i][j].y;
			_z = (float)data->map[i][j].z;
			data->map[i][j].x = (float)((_x * 0.707) + (-0.707 * _y));
			data->map[i][j].y = (float)((_x * 0.408) + (0.408 * _y) + (-0.816 * _z));
		}
	}
}

void	color_screen(t_data *data, int color)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	set_coordinates(data);
	center_map(data);
	iso_transfer(data);
	//center_map(data);
	
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (data->map[i][j].z == 0)
				put_pixel(&data->img, data->map[i][j].x, data->map[i][j].y, color);
			else
				put_pixel(&data->img, data->map[i][j].x, data->map[i][j].y, data->map[i][j].clr);
		}
	}
	set_grid(data);
}

void    set_grid(t_data *data)
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

int     get_slope(int p1, int p2)
{
	if (p1 < p2)
		return (1);
	return(-1);    
}

void    draw_lines(t_point *p1, t_point *p2, t_data *data, int i)
{
	int dx;
	int dy;
	int err;
	int x1 = p1->x;
	int y1 = p1->y;
	
	i = -1;
	dx = abs(p2->x - x1);
	dy = abs(p2->y - y1);
	err = dx - dy;
	while (++i < ft_int_max(dx, dy)) {
		//ft_pixel_put(&data->img, x1, y1, CLR_BLUE);
		put_pixel(&data->img, x1, y1, get_point_color(p1, p2, i, ft_int_max(dx, dy)));
		if (x1 == p2->x && y1 == p2->y) 
			break;
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
