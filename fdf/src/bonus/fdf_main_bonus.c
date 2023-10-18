/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:14:52 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/18 19:35:14 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Set the coordinates for the map points */
void	set_coordinates(t_data *data)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	spc_width = (WIN_W - 100 )/ (data->width - 1);
	spc_height = (WIN_H - 100)/ (data->height - 1);
	if ((spc_height * (data->height - 1) >= WIN_H) ||
		(spc_height * (data->width - 1) >= WIN_W))
		spacing = spc_width;
	else
		spacing = spc_height;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			data->map[i][j].x = 50 + (j * spacing);
			data->map[i][j].y = 50 + (i * spacing);
		}
	}
}

/* Create the first output image in isometric perspective */
void	standard_screen(t_data *data)
{
	data->z_angle = 30;
	set_coordinates(data);
	iso_transfer(data, data->z_angle);
	center_map(data);
	fit_to_window(data, data->z_angle);
	make_gradient(data, CLR_WHITE, CLR_NEON);
}

int 	main(int argc, char **argv) 
{
	t_data 	data;
	time_t	time_bef;

	time(&time_bef);
	if (argc != 2 || ft_checkext(argv[1], ".fdf"))
		args_error();
	process_map(argv[1], &data);
				ft_printf("%ix%i\n", data.width, data.height);
				ft_printf("min:%i max:%i\n", data.z_min, data.z_max);
				ft_printf("range:%i\n", data.z_range);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		ft_error("fdf: ", ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "FdF: jrocha-v");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		ft_error("fdf: ", ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	data.img.mlx_pixel_addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	standard_screen(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	time_bef = time(NULL) - time_bef;
	printf("OK, time: %li s\n", time_bef);
	mlx_hook(data.win_ptr, 17, 0, esc_key, &data);
	mlx_key_hook(data.win_ptr, key_events, &data);
	mlx_loop(data.mlx_ptr);
}
