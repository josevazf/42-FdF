/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:14:52 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/04 16:52:30 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 	main(int argc, char **argv) 
{
	t_init 	*data;
	//t_img	*image;
	
	if (argc != 2)
		args_error();
	data = (t_init*)malloc(sizeof(t_init));
	//image = (t_img*)malloc(sizeof(t_img));
	read_file(argv[1], data);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_error("fdf: ", ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "MLX TESTERRRRR");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		ft_error("fdf: ", ERROR);
	}
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0xFFFFFF);
/* 	image->mlx_img = mlx_new_image(data->mlx_ptr, 4, 4);
	image->addr = mlx_get_data_addr(image->mlx_img, &image->bpp, &image->line_len, &image->endian);
	image->w = 4;
	image->h = 4; */
	mlx_key_hook(data->win_ptr, esc_key, data);
	mlx_loop(data->mlx_ptr);
}
