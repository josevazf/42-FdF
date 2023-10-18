/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:21:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/18 19:12:28 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Esc-Press - close window and free all memory */
int		esc_key(t_data *data)
{
	if (data)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
		ft_free_map(data->map);
		exit (1);
	}
	return (SUCCESS);
}

void	translate_map(t_data *data, int key)
{
	int		i;
	int		j;
	
	i = -1;
	clean_screen(data);
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (key == XK_Up)
				data->map[i][j].y -= 5;
			else if (key == XK_Down)
				data->map[i][j].y += 5;
			else if (key == XK_Left)
				data->map[i][j].x -=5;
			else if (key == XK_Right)
				data->map[i][j].x +=5;
		}
	}
	draw_map(data);
}

void	zoom_map(t_data *data, int key)
{
	clean_screen(data);
	if (key == XK_m)
		scale_height(data, 1.1);
	else if (key == XK_n)
		scale_height(data, 0.9);
	draw_map(data);
}

/* Trigger key press events */
int		key_events(int key, t_data *data)
{
	if (key == XK_m)
		zoom_map(data, XK_m);
	if (key == XK_n)
		zoom_map(data, XK_n);
	if (key == XK_Up)
		translate_map(data, XK_Up);
	if (key == XK_Down)
		translate_map(data, XK_Down);
	if (key == XK_Left)
		translate_map(data, XK_Left);
	if (key == XK_Right)
		translate_map(data, XK_Right);
	if (key == XK_c)
		make_gradient(data, CLR_GREEN, CLR_RED);;
	if (key == XK_Escape)
		esc_key(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (SUCCESS);
}
