/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:10:03 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/18 16:23:22 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	hex_to_rgb(int hex_color, t_point *point)
{
	point->clrRGB.r = (hex_color >> 16) & 0xFF;
	point->clrRGB.g = (hex_color >> 8) & 0xFF;
	point->clrRGB.b = (hex_color & 0xFF);
}

int		get_pnt_color(t_point *p1, t_point *p2, int pos, int len)
{
	int r;
	int g;
	int b;
	float ratio;

	ratio = (float)pos / (float)len;
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
