/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:14:52 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/31 15:59:09 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Set vars to standard values */
void	set_vars(t_data *data)
{
	data->h = 0;
	data->w = 0;
	data->z_max = 0;
	data->z_min = 0;
	data->z_range = 0;
	data->z_ratio = 0;
	data->angle_z = 0;
	data->scale_ratio = 1;
	data->trs_x = 0;
	data->trs_y = 0;
	data->c_pos_x = WIN_W / 2;
	data->c_pos_y = WIN_H / 2;
	data->err = 0;
	data->x1 = 0;
	data->y1 = 0;
	data->z_angle = 30.0;
	data->flag_col = 1;
	data->flag_h = 1;
	data->flag_top = 1;
}

/* Create the first output image in isometric perspective */
void	standard_screen(t_data *data)
{
	clean_screen(data);
	data->flag_top = 1;
	data->angle_z = 0;
	data->z_angle = 30;
	data->c_pos_x = WIN_W / 2;
	data->c_pos_y = WIN_H / 2;
	set_coordinates(data);
	iso_transfer(data, data->z_angle, data->z_ratio);
	translate_center(data, -1, -1);
	fit_to_window(data, data->z_angle);
	if (data->flag_col == 0)
		draw_map(data);
	else
		make_gradient(data, CLR_WHITE, CLR_NEON);
}

/* Trigger key press events */
int	key_events(int key, t_data *data)
{
	if (key == XK_q || key == XK_e)
		scale_height(data, key);
	if (key == XK_a || key == XK_d)
		rotate_map(data, key);
	if (key == XK_w || key == XK_s)
		zoom_map(data, key);
	if (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right)
		translate_map(data, key);
	if (key == XK_1 || key == XK_2 || key == XK_3 || key == XK_4)
		change_colors(data, key);
	if (key == XK_t)
		top_view(data);
	if (key == XK_r)
		standard_screen(data);
	if (key == XK_Escape)
		esc_key(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 
		0, 0);
	menu_controls(data);
	return (SUCCESS);
}

void	menu_controls(t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, 29, 35, CLR_WHITE, 
		"////// CONTROLS //////");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 41, 60, CLR_WHITE, 
		"/");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 46, 60, CLR_WHITE, "\\");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 31, 75, CLR_WHITE, 
		"< + >    move map");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 41, 90, CLR_WHITE, "\\");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 45, 90, CLR_WHITE, 
		"/");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 45, 115, CLR_WHITE, 
		"R      reset map");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 45, 145, CLR_WHITE, 
		"T      top view");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 175, CLR_WHITE, 
		"A/D     rotate view");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 205, CLR_WHITE, 
		"W/S     zoom view");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 235, CLR_WHITE, 
		"Q/E     scale height");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 265, CLR_WHITE, 
		"1-4     change gradient");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 295, CLR_WHITE, 
		"Esc     close window");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || ft_checkext(argv[1], ".fdf"))
		args_error();
	process_map(argv[1], &data);
	data.map_name = ft_strjoin("[jrocha-v]   FdF: ", argv[1]);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		ft_error("fdf: ", ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, data.map_name);
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		ft_error("fdf: ", ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.mlx_pixel_addr = mlx_get_data_addr(data.img.mlx_img, 
			&data.img.bpp, &data.img.line_len, &data.img.endian);
	standard_screen(&data);
	mlx_hook(data.win_ptr, 17, 0, esc_key, &data);
	mlx_key_hook(data.win_ptr, key_events, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	menu_controls(&data);
	mlx_loop(data.mlx_ptr);
}
