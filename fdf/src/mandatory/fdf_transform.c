/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:25:45 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/13 19:39:54 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	center_map(t_data *data)
{
	float	move_x;
	float	move_y;
	int		i;
	int		j;

	move_x = (float)(WINDOW_WIDTH / 2) - get_average(data, 0);
	move_y = (float)(WINDOW_HEIGHT / 2) - get_average(data, 1);
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