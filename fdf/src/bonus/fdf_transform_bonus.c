/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:25:45 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/19 19:47:55 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Scale map with a given factor */
void	scale_map(t_data *data, double factor)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
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
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
				data->map[i][j].x = data->map[i][j].x + move_x;
				data->map[i][j].y = data->map[i][j].y + move_y;
		}
	}
}

/* Convert from top view to isometric projection */
void	iso_transfer(t_data *data, double angle)
{
	float	x;
	float	y;
	float	z;
	int		i;
	int		j;
	
	i = -1;
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
			x = (float)data->map[i][j].x;
			y = (float)data->map[i][j].y;
			z = (float)data->map[i][j].z;
			data->map[i][j].x = (float)((x - y) * cos(get_rad(angle)));
			data->map[i][j].y = (float)((x + y) * sin(get_rad(angle)) - 
			(z * data->z_ratio));
		}
	}
}

/* Fit isometric view to window */
void	fit_to_window(t_data *data, double angle)
{
	double ratio;

	ratio = 1;
	while ((data->map[data->h - 1][data->w - 1].y - 
		data->map[0][0].y >= WIN_H - 300))
	{
		if (data->map[data->h - 1][data->w - 1].y - 
		data->map[0][0].y >= WIN_H - 300)
		{
			set_coordinates(data);
			scale_map(data, pow(0.9, ratio));
		}
		else if (data->map[data->h - 1][data->w - 1].y - 
		data->map[0][0].y <= WIN_H / 2)
		{
			set_coordinates(data);
			scale_map(data, pow(1.1, ratio));
		}
	iso_transfer(data, angle);
	center_map(data);
	ratio = ratio + 1;
	}
}

/* Scale map with a given factor */
void	scale_h(t_data *data, double factor)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
			data->map[i][j].z = (double)data->map[i][j].z * factor;
	}
}
