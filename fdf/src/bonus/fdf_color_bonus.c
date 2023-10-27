/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:10:03 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/27 10:30:41 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Converts hex RGB representation to each value of r, g and b */
void	hex_to_rgb(int hex_color, t_point *point)
{
	point->rgb.r = (hex_color >> 16) & 0xFF;
	point->rgb.g = (hex_color >> 8) & 0xFF;
	point->rgb.b = (hex_color & 0xFF);
}

/* Get the color for the gradient point between p1 and p2*/
int	get_pnt_color(t_point *p1, t_point *p2, float pos, int len)
{
	int		r;
	int		g;
	int		b;
	float	ratio;

	ratio = pos / (float)len;
	hex_to_rgb(p1->clr, p1);
	hex_to_rgb(p2->clr, p2);
	if ((p1->clr == p2->clr) || len == 0)
		return (p1->clr);
	else
	{
		r = p1->rgb.r + ((p2->rgb.r - p1->rgb.r) * ratio);
		g = p1->rgb.g + ((p2->rgb.g - p1->rgb.g) * ratio);
		b = p1->rgb.b + ((p2->rgb.b - p1->rgb.b) * ratio);
		return (r << 16 | g << 8 | b);
	}
}

/* Get the color for all the map points given the gradient */
void	make_gradient(t_data *data, int clr1, int clr2)
{
	int		i;
	int		j;
	float	pnt_pos;
	t_point	*p1;
	t_point	*p2;

	i = -1;
	j = -1;
	p1 = malloc(sizeof(t_point));
	p2 = malloc(sizeof(t_point));
	p1->clr = clr1;
	p2->clr = clr2;
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
			pnt_pos = get_pnt_position(data->map[i][j].z, data);
			data->map[i][j].clr = get_pnt_color(p1, p2, pnt_pos, data->z_range);
		}
	}
	draw_map(data);
	free(p1);
	free(p2);
}

int	terrain_fade(int z)
{
	if (z > 1100)
		return (0xE9EAF0);
	if (z > 600)
		return (0xC4C1BD);
	if (z > 500)
		return (0x4C591A);
	if (z > 100)
		return (0x4C591A);
	if (z > 10)
		return (0x4D5E36);
	if (z > 0)
		return (0xD8D19C);
	if (z > -50)
		return (0x444CC6);
	if (z > -100)
		return (0x2A2EAE);
	if (z > -300)
		return (0x3D497C);
	return (0x05093d);
}

void	set_terrain(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
			data->map[i][j].clr = terrain_fade(data->map[i][j].z);
	}
	data->flag_col = 0;
	draw_map(data);
}
