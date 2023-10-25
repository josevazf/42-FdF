/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transf2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:35:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/25 10:24:40 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Get center of map representation */
void	get_map_center(t_data *data)
{
	data->c_pos_x = get_average(data, 0);
	data->c_pos_y = get_average(data, 1);
}

/* Rotate around Z axis by the center of the map  */
void	rotate_x(t_data *data, double angle, int i, int j)
{
	int		y1;
	int		z1;
	int		y2;
	int		z2;
	double	ang;
	
	data->angle_x = angle;
	ang = get_rad(data->angle_x);
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
			y1 = (data->map[i][j].y - data->c_pos_y);
			z1 = (data->map[i][j].z - (data->z_range / 2));
			y2 = y1 * cos(ang) - z1 * sin(ang);
			z2 = y1 * sin(ang) + z1 * cos(ang);
			data->map[i][j].y = y2 + data->c_pos_y;
			data->map[i][j].z = (z2 + (data->z_range / 2));
		}
	}
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
