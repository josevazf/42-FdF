/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:14:52 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/14 18:30:49 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 	main(int argc, char **argv) 
{
	t_data 	data;
	
	if (argc != 2)
		args_error();
	process_map(argv[1], &data);
	ft_printf("%ix%i\n", data.width, data.height);
	ft_printf("min:%i max:%i\n", data.z_min, data.z_max);
	ft_printf("range:%i\n", data.range);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		ft_error("fdf: ", ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "MLX TESTERRRRR");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		ft_error("fdf: ", ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.mlx_pixel_addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	color_screen(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	mlx_key_hook(data.win_ptr, key_events, &data);
	mlx_loop(data.mlx_ptr);
}
