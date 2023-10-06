/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:27:29 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/06 17:41:54 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_height(char *file_name)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	line = NULL;
	fd = open(file_name, O_RDONLY, 0);
	fd_error(fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		height++;
		free(line);		
	}
	close(fd);
	return (height);
}

int		get_width(char *file_name)
{
	int		fd;
	int		width;
	char	*line;

	width = 0;
	fd = open(file_name, O_RDONLY, 0);
	fd_error(fd);
	line = get_next_line(fd);
	width = ft_count_words(line);
	free(line);
	close(fd);
	return (width);
}

void	create_matrix(t_data *data)
{
	int	i;

	i = -1;
	data->alt_matrix = (int **)malloc(sizeof(int *) * (data->height + 1));
	malloc_error(data->alt_matrix);	
	while (++i < data->height)
	{
		data->alt_matrix[i] = (int *)malloc(sizeof(int) * (data->width + 1));
		malloc_error(data->alt_matrix[i]);	
	}
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
	altitude[i] = '\0';
	free(nums);
}

void	read_file(char *file_name, t_data *data)
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
	fd_error(fd);
	create_matrix(data);
	while (++i < data->height)
	{
		line = get_next_line(fd);
		fill_matrix(data->alt_matrix[i], line);
		free(line);
	}
	line = get_next_line(fd);
	free(line);
	close(fd);
	data->alt_matrix[i] = NULL;
	ft_print_imatrix(data->alt_matrix, data->height, data->width);
}
