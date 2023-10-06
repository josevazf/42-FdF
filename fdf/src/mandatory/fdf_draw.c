/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:31:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/06 13:07:29 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));

	*((unsigned int *)(offset + img->mlx_pixel_addr)) = color;
}

void	color_screen(t_init *data, int color)
{
	for (int y = 0; y < WINDOW_WIDTH; ++y)
	{
		for (int x = 0; x < WINDOW_WIDTH; ++x)
		{
			ft_pixel_put(&data->img, x, y, color);
		}
	}
}
