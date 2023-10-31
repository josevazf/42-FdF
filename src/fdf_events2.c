/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:44:42 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/31 15:59:05 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Change color representation */
void	change_colors(t_data *data, int key)
{
	if (key == XK_1)
		make_gradient(data, CLR_WHITE, CLR_WHITE);
	if (key == XK_2)
		make_gradient(data, CLR_GREEN, CLR_RED);
	if (key == XK_3)
		make_gradient(data, CLR_BLACK, CLR_NEON);
	if (key == XK_4)
		set_terrain(data);
}
