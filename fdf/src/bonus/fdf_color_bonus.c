/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:10:03 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/25 19:48:20 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Converts hex RGB representation to each value of r, g and b */
void	hex_to_rgb(int hex_color, t_point *point)
{
	point->clrRGB.r = (hex_color >> 16) & 0xFF;
	point->clrRGB.g = (hex_color >> 8) & 0xFF;
	point->clrRGB.b = (hex_color & 0xFF);
}

/* Get the color for the gradient point between p1 and p2*/
int		get_pnt_color(t_point *p1, t_point *p2, float pos, int len)
{
	int r;
	int g;
	int b;
	float ratio;

	ratio = pos / (float)len;
	hex_to_rgb(p1->clr, p1);
	hex_to_rgb(p2->clr, p2);
	if ((p1->clr == p2->clr) || len == 0)
		return (p1->clr);
	else
	{
		r = p1->clrRGB.r + ((p2->clrRGB.r - p1->clrRGB.r) * ratio);
		g = p1->clrRGB.g + ((p2->clrRGB.g - p1->clrRGB.g) * ratio);
		b = p1->clrRGB.b + ((p2->clrRGB.b - p1->clrRGB.b) * ratio);
		return (r << 16 | g << 8 | b);
	}
}

/* Get the color for all the map points given the gradient */
void	make_gradient(t_data *data, int clr1, int clr2, int clr3, int trg)
{
	int 	i;
	int		j;
	float	pnt_pos;
	t_point *p1;
	t_point *p2;
	
	i = -1;
	j = -1;
	p1 = malloc(sizeof(t_point));
	p2 = malloc(sizeof(t_point));
	while (++i < data->h)
	{
		p1->clr = clr1;
		p2->clr = clr3;
		j = -1;
		while (++j < data->w)
		{
			p1->clr = clr1;
			p2->clr = clr3;
			pnt_pos = get_pnt_position(data->map[i][j].z, data);
			if ((pnt_pos < data->z_range / 2) && trg != 0)
			{
				p2->clr = clr2;
				data->map[i][j].clr = get_pnt_color(p1, p2, pnt_pos, data->z_range / 2);
			}
			else if ((pnt_pos == data->z_range / 2) && trg != 0)
				data->map[i][j].clr = clr2;
			else if ((pnt_pos > data->z_range / 2) && trg != 0)
			{
				p1->clr = clr2;
				data->map[i][j].clr = get_pnt_color(p1, p2, pnt_pos, data->z_range / 2);
			}
			else
				data->map[i][j].clr = get_pnt_color(p1, p2, pnt_pos, data->z_range);
		}
	}
	draw_map(data);
	free(p1);
	free(p2);
}

/* Fills the screen with black pixels */
void	clean_screen(t_data *data)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < WIN_W)
	{
		j = -1;
		while (++j < WIN_H)
			put_pixel(&data->img, i, j, CLR_BLACK);
	}
}
