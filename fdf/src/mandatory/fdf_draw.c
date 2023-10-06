/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:31:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/06 18:16:26 by jrocha-v         ###   ########.fr       */
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

void	color_screen(t_data *data, int color)
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
			if (data->alt_matrix[i][j] == 0)
				ft_pixel_put(&data->img, 100 + (j * spacing), 100 + (i * spacing), 0xFFFFFF);
			else
				ft_pixel_put(&data->img, 100 + (j * spacing), 100 + (i * spacing), color);
		}
	}
}
