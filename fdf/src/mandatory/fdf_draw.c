/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:31:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/09 19:05:01 by jrocha-v         ###   ########.fr       */
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

void	set_coordinates(t_data *data)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	spc_width = (WINDOW_WIDTH - 100) / (data->width - 1);
	spc_height = (WINDOW_HEIGHT - 100) / (data->height - 1);
	if (spc_height * data->height > WINDOW_HEIGHT)
		spacing = spc_width;
	else
		spacing = spc_height;
	//spacing = ft_int_max(spc_width, spc_height);
	//spacing = 2;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
				data->map[i][j].x = 50 + (j * spacing);
				data->map[i][j].y = 50 + (i * spacing);
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
	set_coordinates(data);
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
