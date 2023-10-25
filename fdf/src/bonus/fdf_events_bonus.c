/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:21:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/25 17:46:58 by jrocha-v         ###   ########.fr       */
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
	scale_map(data, data->scale_ratio);
	if (key == XK_g)
		rotate_x(data, data->angle_x + 5, -1, -1);
	if (key == XK_b)
		rotate_x(data, data->angle_x - 5, -1, -1);
	if (key == XK_d)
		rotate_z(data, data->angle_z + 5, -1, -1);
	if (key == XK_a)
		rotate_z(data, data->angle_z - 5, -1, -1);
	if (data->flag_top != 0)
		iso_transfer(data, data->z_angle, data->z_ratio * data->scale_ratio);
	translate_center(data, -1, -1);
	draw_map(data);
}

void	top_view(t_data *data)
{
	data->flag_top = 0;
	data->z_angle = 0;
	data->angle_x = 0;
	data->angle_z = 0;
	clean_screen(data);
	scale_map(data, data->scale_ratio);
	translate_center(data, -1, -1);
	draw_map(data);
}

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

void	zoom_map(t_data *data, int key)
{
	clean_screen(data);
	if (key == XK_w)
		scale_map(data, data->scale_ratio * 1.1);
	if (key == XK_s)
		scale_map(data, data->scale_ratio * 0.9);
	if (data->angle_x != 0)
		rotate_x(data, data->angle_x, -1, -1);
	if (data->angle_z != 0)
		rotate_z(data, data->angle_z, -1, -1);
	if (data->z_angle != 0)
		iso_transfer(data, data->z_angle, data->z_ratio * data->scale_ratio);
	translate_center(data, -1, -1);
	draw_map(data);
}

/* Trigger key press events */
int		key_events(int key, t_data *data)
{
	if (key == XK_a || key == XK_d || key == XK_g || key == XK_b)
		rotate_map(data, key);
	if (key == XK_w || key == XK_s)
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
	menu_info(data);
	menu_controls(data);
	return (SUCCESS);
}
