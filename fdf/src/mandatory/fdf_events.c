/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:21:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/27 08:44:37 by jrocha-v         ###   ########.fr       */
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
		ft_free_map(data->map);
		exit (EXIT_SUCCESS);
	}
	return (SUCCESS);
}

/* Trigger key press events */
int	key_events(int key, t_data *data)
{
	if (key == XK_Escape)
		esc_key(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, 
		data->img.mlx_img, 0, 0);
	return (0);
}
