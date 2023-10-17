/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:25:45 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/17 18:54:56 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Scale map with a given factor */
void	scale_map(t_data *data, double factor)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
				data->map[i][j].x = (double)data->map[i][j].x * factor;
				data->map[i][j].y = (double)data->map[i][j].y * factor;
		}
	}
}

/* Center map on the window */
void	center_map(t_data *data)
{
	float	move_x;
	float	move_y;
	int		i;
	int		j;

	move_x = (float)(WIN_W / 2) - get_average(data, 0);
	move_y = (float)(WIN_H / 2) - get_average(data, 1);
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

/* Convert from top view to isometric projection */
void	iso_transfer(t_data *data)
{
	float	x;
	float	y;
	float	z;
	int		i;
	int		j;
	
	printf("%f", data->z_ratio);
	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			x = (float)data->map[i][j].x;
			y = (float)data->map[i][j].y;
			z = (float)data->map[i][j].z;
			data->map[i][j].x = (float)((x - y) * cos(0.5236));
			data->map[i][j].y = (float)((x + y) * sin(0.5236) - 
			(z * 1));
		}
	}
}

/* Fit isometric view to window */
void	fit_to_window(t_data *data)
{
	double ratio;

	ratio = 1;
	while ((data->map[data->height - 1][data->width - 1].y - 
		data->map[0][0].y >= WIN_H - 500))
	{
		if (data->map[data->height - 1][data->width - 1].y - 
		data->map[0][0].y >= WIN_H - 500)
		{
			set_coordinates(data);
			scale_map(data, pow(0.9, ratio));
		}
		else if (data->map[data->height - 1][data->width - 1].y - 
		data->map[0][0].y <= WIN_H / 2)
		{
			set_coordinates(data);
			scale_map(data, pow(1.1, ratio));
		}
	iso_transfer(data);
	center_map(data);
	ratio = ratio + 1;
	}
}