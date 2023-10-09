/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:10:03 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/09 17:48:50 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	get_ratio(int min, int max, int cur)
{
	double	ratio;

	if (min == max)
		return (1.0);
	ratio = (double)(cur - min) / (max - min);
	return (ratio);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_default_clr(int z, t_point *map)
{
	double	ratio;

	ratio = get_ratio(map->z_min, map->z_max, z);
	if (ratio < 0.2)
		return (CLR_DISCO);
	else if (ratio < 0.4)
		return (CLR_BRICK_RED);
	else if (ratio < 0.6)
		return (CLR_FLAMINGO);
	else if (ratio < 0.8)
		return (CLR_JAFFA);
	else
		return (CLR_SAFFRON);
}

/* static int	do_lerp(int min, int max, double ratio)
{
	return ((int)((ratio) * min + (1 - ratio) * max));
} */

/*
** Quadrant 1, 4, 5, 8(delta.x > delta.y): sample by x
** Quadrant 2, 3, 6, 7(delta.x < delta.y): sample by y
*/

int	get_clr(t_point cur, t_point *min, t_point *max, t_point delta)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	if (cur.clr == max->clr)
		return (cur.clr);
	if (delta.x > delta.y)
		ratio = get_ratio(min->x, max->x, cur.x);
	else
		ratio = get_ratio(min->y, max->y, cur.y);
	red = do_lerp((max->clr >> 16) & 0xFF, (min->clr >> 16) & 0xFF, ratio);
	green = do_lerp((max->clr >> 8) & 0xFF, (min->clr >> 8) & 0xFF, ratio);
	blue = do_lerp(max->clr & 0xFF, min->clr & 0xFF, ratio);
	return ((red << 16) | (green << 8) | blue);
}