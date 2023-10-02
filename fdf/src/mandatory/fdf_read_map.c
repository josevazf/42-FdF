/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:27:29 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/02 18:56:33 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_height(char *file_name)
{
	int	fd;
	int	height;

	height = 0;
	fd = open(file_name, O_RDONLY, 0);
	while (get_next_line(fd))
		height++;
	close(fd);
	return (height);
}

int		get_width(char *file_name)
{
	int	fd;
	int	width;

	width = 0;
	fd = open(file_name, O_RDONLY, 0);
	width = ft_count_words(get_next_line(fd));
	close(fd);
	return (width);
}

void	read_file(char *file_name, fdf_init *data)
{
	data->height = get_height(file_name);
		ft_printf("%i\n", data->height);
	data->width = get_width(file_name);
		ft_printf("%i\n", data->width);
	
}
