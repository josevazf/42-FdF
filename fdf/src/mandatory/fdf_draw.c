/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:31:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/18 16:32:26 by jrocha-v         ###   ########.fr       */
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

/* Draw map by vertical and horizontal lines */
void    draw_map(t_data *data)
{
	vertical_lines(data);
	horizontal_lines(data);
}	

/* Define and draw vertical lines */
void	vertical_lines(t_data *data)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < data->height - 1)
	{
		j = -1;
		while (++j < (data->width))
		{
			data->x1 = data->map[i][j].x;
			data->y1 = data->map[i][j].y;
			draw_lines(&data->map[i][j], &data->map[i + 1][j], data, -1);
		}
	}
}

/* Define and draw horizontal lines */
void	horizontal_lines(t_data *data)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++j < data->width - 1)
	{
		i = -1;
		while (++i < data->height)
		{
			data->x1 = data->map[i][j].x;
			data->y1 = data->map[i][j].y;
			draw_lines(&data->map[i][j], &data->map[i][j + 1], data, -1);
		}
	}
}

/* Draw lines with gradient between p1 and p2 */
void    draw_lines(t_point *p1, t_point *p2, t_data *data, int i)
{
	int dx;
	int dy;

	dx = abs(p2->x - data->x1);
	dy = abs(p2->y - data->y1);
	data->err = dx - dy;
	while (++i < ft_int_max(dx, dy))
	{
		if (data->x1 > 0 && data->x1 < WIN_W - 5 && data->y1 > 0 && 
		data->y1 < WIN_H - 5)
			put_pixel(&data->img, data->x1, data->y1, get_pnt_color(p1, p2, i, 
			ft_int_max(dx, dy)));
		if (data->x1 == p2->x && data->y1 == p2->y)
			break ;
		if (2 * data->err > -dy)
		{
			data->err -= dy;
			data->x1 += get_slope(data->x1, p2->x);
		}
		if (2 * data->err < dx)
		{
			data->err += dx;
			data->y1 += get_slope(data->y1, p2->y);
		}
	}
}
