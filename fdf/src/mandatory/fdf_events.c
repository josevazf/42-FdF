/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:21:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/13 18:02:57 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_map(t_point **matrix)
{
	int	i;
	
	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int		esc_key(int key, t_data *data)
{
	int 	i;
	int 	j;
	int 	dif;
	int		point;
	t_point *p1;
	t_point *p2;
	
	i = -1;
	j = -1;
	p1 = malloc(sizeof(t_point));
	p2 = malloc(sizeof(t_point));
	dif = abs(data->z_max - data->z_min);
	p1->clr = CLR_GREEN;
	p2->clr = CLR_RED;
	if (key == XK_c)
	{
		while (++i < data->height)
		{
			j = -1;
			while (++j < data->width)
			{
				point = data->map[i][j].z + data->z_max;
				data->map[i][j].clr = get_point_color(p1, p2, point, dif);
			}
		}
		color_screen(data);
	}
	if (key == XK_Escape)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		data->win_ptr = NULL;
		free(data->mlx_ptr);
		ft_free_map(data->map);
		//free(data);
		free(p1);
		free(p2);
		exit (1);
	}
	//color_screen(data);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}
