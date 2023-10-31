/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:21:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/31 15:58:44 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Esc-Press - close window and free all memory */
int	esc_key(t_data *data)
{
	if (data)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
		free(data->map_name);
		ft_free_map(data->map);
		exit (EXIT_SUCCESS);
	}
	return (SUCCESS);
}

/* Change height representation */
int	scale_height(t_data *data, int key)
{
	if (data->flag_top == 0)
		return (1);
	clean_screen(data);
	scale_map(data, data->scale_ratio);
	if (data->angle_z != 0)
		rotate_z(data, data->angle_z, -1, -1);
	if (key == XK_q)
	{
		data->z_ratio = data->z_ratio * 1.1;
		iso_transfer(data, data->z_angle, data->z_ratio * data->scale_ratio);
	}
	if (key == XK_e)
	{
		data->z_ratio = data->z_ratio * 0.9;
		iso_transfer(data, data->z_angle, data->z_ratio * data->scale_ratio);
	}
	translate_center(data, -1, -1);
	draw_map(data);
	return (0);
}

/* Rotate map around a centered Z Axis */
void	rotate_map(t_data *data, int key)
{
	clean_screen(data);
	scale_map(data, data->scale_ratio);
	if (key == XK_d)
		rotate_z(data, data->angle_z + 5, -1, -1);
	if (key == XK_a)
		rotate_z(data, data->angle_z - 5, -1, -1);
	if (data->flag_top != 0)
		iso_transfer(data, data->z_angle, data->z_ratio * data->scale_ratio);
	translate_center(data, -1, -1);
	draw_map(data);
}

/* Translate map in 4 directions */
void	translate_map(t_data *data, int key)
{
	clean_screen(data);
	if (key == XK_Up)
		data->trs_y += 5;
	else if (key == XK_Down)
		data->trs_y -= 5;
	else if (key == XK_Left)
		data->trs_x += 5;
	else if (key == XK_Right)
		data->trs_x -= 5;
	translate_center(data, -1, -1);
	draw_map(data);
	data->trs_x = 0;
	data->trs_y = 0;
}

/* Zoom map in and out */
void	zoom_map(t_data *data, int key)
{
	clean_screen(data);
	if (key == XK_w)
		scale_map(data, data->scale_ratio * 1.1);
	if (key == XK_s)
		scale_map(data, data->scale_ratio * 0.9);
	if (data->angle_z != 0)
		rotate_z(data, data->angle_z, -1, -1);
	if (data->z_angle != 0)
		iso_transfer(data, data->z_angle, data->z_ratio * data->scale_ratio);
	translate_center(data, -1, -1);
	draw_map(data);
}
