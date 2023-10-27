/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transf1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:25:45 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/27 10:36:31 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Set coordinates for standard map values */
void	set_coordinates(t_data *data)
{
	int	spc_h;
	int	spc_w;
	int	spacing;
	int	i;
	int	j;

	i = -1;
	j = -1;
	spc_w = (WIN_W - 100) / (data->w - 1);
	spc_h = (WIN_H - 100) / (data->h - 1);
	if ((spc_h * (data->h - 1) >= WIN_H) || 
		(spc_h * (data->w - 1) >= WIN_W))
		spacing = spc_w;
	else
		spacing = spc_h;
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
			data->map[i][j].x = 50 + (j * spacing);
			data->map[i][j].y = 50 + (i * spacing);
		}
	}
}

/* Scale map with a given factor */
void	scale_map(t_data *data, double factor)
{
	int		i;
	int		j;

	i = -1;
	set_coordinates(data);
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
			data->map[i][j].x = (double)data->map[i][j].x * factor;
			data->map[i][j].y = (double)data->map[i][j].y * factor;
		}
	}
	data->scale_ratio = factor;
}

/* Center map on the window */
void	translate_center(t_data *data, int i, int j)
{
	float	move_x;
	float	move_y;

	i = -1;
	if (data->trs_x != 0 || data->trs_y != 0)
	{
		move_x = data->trs_x;
		move_y = data->trs_y;
	}
	else
	{
		move_x = data->c_pos_x - get_average(data, 0);
		move_y = data->c_pos_y - get_average(data, 1);
	}
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
			data->map[i][j].x = data->map[i][j].x + move_x;
			data->map[i][j].y = data->map[i][j].y + move_y;
		}
	}
	get_map_center(data);
}

/* Convert from top view to isometric projection */
void	iso_transfer(t_data *data, double angle, float ratio)
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
					(z * ratio));
		}
	}
	data->z_angle = angle;
}

/* Fit isometric view to window */
void	fit_to_window(t_data *data, double angle)
{
	double	ratio;

	ratio = 1;
	while ((data->map[data->h - 1][data->w - 1].y - 
		data->map[0][0].y >= WIN_H - 300))
	{
		if (data->map[data->h - 1][data->w - 1].y - 
		data->map[0][0].y >= WIN_H - 300)
			scale_map(data, pow(0.9, ratio));
		else if (data->map[data->h - 1][data->w - 1].y - 
		data->map[0][0].y <= WIN_H / 2)
			scale_map(data, pow(1.1, ratio));
		iso_transfer(data, angle, data->z_ratio * data->scale_ratio);
		translate_center(data, -1, -1);
		ratio = ratio + 1;
	}
}
