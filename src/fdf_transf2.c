/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transf2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:35:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/31 15:59:43 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Fills the screen with black pixels */
void	clean_screen(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < WIN_W)
	{
		j = -1;
		while (++j < WIN_H)
			put_pixel(&data->img, i, j, CLR_BLACK);
	}
}

/* Get center of map representation */
void	get_map_center(t_data *data)
{
	data->c_pos_x = get_average(data, 0);
	data->c_pos_y = get_average(data, 1);
}

/* Rotate around Z axis by the center of the map */
void	rotate_z(t_data *data, double angle, int i, int j)
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	double	ang;

	data->angle_z = angle;
	ang = get_rad(data->angle_z);
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
			x1 = (data->map[i][j].x - data->c_pos_x);
			y1 = (data->map[i][j].y - data->c_pos_y);
			x2 = x1 * cos(ang) - y1 * sin(ang);
			y2 = x1 * sin(ang) + y1 * cos(ang);
			data->map[i][j].x = x2 + data->c_pos_x;
			data->map[i][j].y = y2 + data->c_pos_y;
		}
	}
}

/* Transform map to Top View */
void	top_view(t_data *data)
{
	data->flag_top = 0;
	data->z_angle = 0;
	data->angle_z = 0;
	clean_screen(data);
	scale_map(data, data->scale_ratio);
	translate_center(data, -1, -1);
	draw_map(data);
}
