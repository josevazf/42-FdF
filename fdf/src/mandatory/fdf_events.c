/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:21:05 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/14 18:35:03 by jrocha-v         ###   ########.fr       */
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

void	esc_key(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	data->win_ptr = NULL;
	free(data->mlx_ptr);
	ft_free_map(data->map);
	exit (1);
}

float		get_point_c(float z, t_data *data)
{
	float norm;
	
	norm = (z - data->z_min) / (data->z_max - data->z_min);
	return (norm * data->range);
}

void	c_key(t_data *data)
{
	int 	i;
	int 	j;
	int		point;
	t_point *p1;
	t_point *p2;
	
	i = -1;
	j = -1;
	p1 = malloc(sizeof(t_point));
	p2 = malloc(sizeof(t_point));
	p1->clr = CLR_GREEN;
	p2->clr = CLR_RED;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			point = get_point_c(data->map[i][j].z, data);
			data->map[i][j].clr = get_point_color(p1, p2, point, data->range);
		}
	}
	color_screen(data);
	free(p1);
	free(p2);
}

int		key_events(int key, t_data *data)
{
	if (key == XK_c)
		c_key(data);
	if (key == XK_Escape)
		esc_key(data);
	//color_screen(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}
