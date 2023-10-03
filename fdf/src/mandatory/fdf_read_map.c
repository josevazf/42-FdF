/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:27:29 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/03 11:28:20 by jrocha-v         ###   ########.fr       */
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

void	fill_matrix(int *altitude, char *line)
{
	char	**nums;
	int		i;

	i = -1;
	nums = ft_split(line, ' ');
	while (nums[++i])
	{
		altitude[i] = ft_atoi(nums[i]);
		free(nums[i]);
	}
	free(nums[i]);	
}

void	ft_print_imatrix(int **matrix, int height, int width)
{
	int i;
	int j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			ft_printf("%i\t", matrix[i][j]);
		ft_printf("\n");
	}
}

void	read_file(char *file_name, fdf_init *data)
{
	char	*line;
	int 	i;
	int 	fd;

	i = -1;
	data->height = get_height(file_name);
		ft_printf("%i\n", data->height);
	data->width = get_width(file_name);
		ft_printf("%i\n", data->width);
	fd = open(file_name, O_RDONLY, 0);
	data->altitude = (int **)malloc(sizeof(int *) * (data->height));
	while (++i < data->height)
		data->altitude[i] = (int *)malloc(sizeof(int) * (data->width));
	i = -1;
	while (++i < data->height)
	{
		line = get_next_line(fd);
		fill_matrix(data->altitude[i], line);
	}
	ft_print_imatrix(data->altitude, data->height, data->width);
	close(fd);
}
