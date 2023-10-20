/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:21:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/20 19:49:51 by jrocha-v         ###   ########.fr       */
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
		exit (EXIT_SUCCESS);
	}
	return (SUCCESS);
}

void	rotate_map(t_data *data, int key)
{
	clean_screen(data);
	if (key == XK_h)
	{
		scale_map(data, data->scale_ratio);
		iso_transfer(data, data->z_angle + 5, data->z_ratio * data->scale_ratio);
	}
	if (key == XK_n)
	{
		scale_map(data, data->scale_ratio);
		iso_transfer(data, data->z_angle - 5, data->z_ratio * data->scale_ratio);
	}	
	translate_center(data);
	draw_map(data);
}

void	top_view(t_data *data)
{
	clean_screen(data);
	set_coordinates(data);
	translate_center(data);
	draw_map(data);
}

void	translate_map(t_data *data, int key)
{
	clean_screen(data);
	if (key == XK_Up)
		data->c_pos_y += 5;
	else if (key == XK_Down)
		data->c_pos_y -= 5;
	else if (key == XK_Left)
		data->c_pos_x += 5;
	else if (key == XK_Right)
		data->c_pos_x -= 5;
	translate_center(data);
	draw_map(data);
}

void	zoom_map(t_data *data, int key)
{
	clean_screen(data);
	if (key == XK_j)
		scale_map(data, data->scale_ratio * 1.1);
	if (key == XK_m)
		scale_map(data, data->scale_ratio * 0.9);
	iso_transfer(data, data->z_angle, data->z_ratio * data->scale_ratio);
	translate_center(data);
	draw_map(data);
}

/* Trigger key press events */
int		key_events(int key, t_data *data)
{
	if (key == XK_h || key == XK_n)
		rotate_map(data, key);
	if (key == XK_j || key == XK_m)
		zoom_map(data, key);
	if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right)
		translate_map(data, key);
	if (key == XK_c)
		make_gradient(data, CLR_GREEN, CLR_RED);
	if (key == XK_t)
		top_view(data);
	if (key == XK_r)
		standard_screen(data);
	if (key == XK_Escape)
		esc_key(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (SUCCESS);
}
