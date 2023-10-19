/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:16:36 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/19 19:48:13 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Get center point for x ->(t = 0) else y */
float	get_average(t_data *data, int t)
{
	float v1;
	float v2;
	float v3;
	float v4;

	if (t == 0)
	{
		v1 = (float)data->map[0][0].x;
		v2 = (float)data->map[0][data->w - 1].x;
		v3 = (float)data->map[data->h - 1][0].x;
		v4 = (float)data->map[data->h - 1][data->w - 1].x;
	}
	else
	{
		v1 = (float)data->map[0][0].y;
		v2 = (float)data->map[0][data->w - 1].y;
		v3 = (float)data->map[data->h - 1][0].y;
		v4 = (float)data->map[data->h - 1][data->w - 1].y;
	}
	return ((v1 + v2 + v3 + v4) / 4);
}

/* Get the position of the point relative to total h */
float	get_pnt_position(float z, t_data *data)
{
	float norm;
	
	norm = (z - data->z_min) / (data->z_max - data->z_min);
	return (norm * data->z_range);
}

/* Get direction to draw line */
int     get_slope(int p1, int p2)
{
	if (p1 < p2)
		return (1);
	return(-1);
}

/* Get value to smooth Z representation */
void	get_zratio(t_data *data)
{
	if (data->z_range == 0)
		data->z_ratio = 1;
	else
		data->z_ratio = 35.3832 * pow(data->z_range, -1.0655);
}

/* Convert degrees to radians */
double	get_rad(double deg)
{
	return (deg * M_PI / 180);
}
