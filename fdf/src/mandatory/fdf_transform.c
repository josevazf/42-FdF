/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:25:45 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/16 14:17:44 by jrocha-v         ###   ########.fr       */
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

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			x = (float)data->map[i][j].x;
			y = (float)data->map[i][j].y;
			z = (float)data->map[i][j].z;
			data->map[i][j].x = (float)((x * 0.707) + (-0.707 * y));
			data->map[i][j].y = (float)((x * 0.408) + (0.408 * y) + (-0.816 * z));
		}
	}
}
