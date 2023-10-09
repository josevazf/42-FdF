/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:31:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/09 16:10:42 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_int_max(int x, int y)
{
	if (x >= y)
		return (x);
	else
		return (y);
}

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));

	*((unsigned int *)(offset + img->mlx_pixel_addr)) = color;
}

void	ft_set_coordinates(t_data *data)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	spc_width = (WINDOW_WIDTH - 200) / (data->width - 1);
	spc_height = (WINDOW_HEIGHT - 200) / (data->height - 1);
	//spacing = ft_int_max(spc_width, spc_height);
	spacing = 10;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
				data->map[i][j].x = 100 + (j * spacing);
				data->map[i][j].y = 100 + (i * spacing);
		}
	}
}

void	color_screen(t_data *data, int color)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (data->map[i][j].z == 0)
				ft_pixel_put(&data->img, data->map[i][j].x, data->map[i][j].y, color);
			else
				ft_pixel_put(&data->img, data->map[i][j].x, data->map[i][j].y, data->map[i][j].clr);
		}
	}
}
