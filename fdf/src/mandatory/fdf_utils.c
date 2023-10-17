/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:16:36 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/17 18:22:08 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		v2 = (float)data->map[0][data->width - 1].x;
		v3 = (float)data->map[data->height - 1][0].x;
		v4 = (float)data->map[data->height - 1][data->width - 1].x;
	}
	else
	{
		v1 = (float)data->map[0][0].y;
		v2 = (float)data->map[0][data->width - 1].y;
		v3 = (float)data->map[data->height - 1][0].y;
		v4 = (float)data->map[data->height - 1][data->width - 1].y;
	}
	return ((v1 + v2 + v3 + v4) / 4);
}

/* Get the position of the point relative to total height */
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

