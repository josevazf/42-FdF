/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:14:52 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/03 10:54:56 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 	main(int argc, char **argv) 
{
	fdf_init *data;
	
	if (argc != 2)
		exit(ERROR);
	
	data = (fdf_init*)malloc(sizeof(fdf_init));
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
	mlx_key_hook(data->win_ptr, press_key, data);
	mlx_loop(data->mlx_ptr);

	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data->win_ptr);
}
