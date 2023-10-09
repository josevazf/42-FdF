/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:27:29 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/09 16:11:17 by jrocha-v         ###   ########.fr       */
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
	data->map = (t_point **)malloc(sizeof(t_point *) * (data->height + 1));
	malloc_error(data->map);	
	while (++i < data->height)
	{
		data->map[i] = (t_point *)malloc(sizeof(t_point) * (data->width + 1));
		malloc_error(data->map[i]);	
	}
}

void	fill_matrix(t_point *map, char *line)
{
	char	**nums;
	int		i;

	i = -1;
	nums = ft_split(line, ' ');
	while (nums[++i])
	{
		map[i].x = 0;
		map[i].y = 0;
		map[i].z = ft_atoi(nums[i]);
		if (!ft_strchr(nums[i], ','))
			map[i].clr = 0xFFFFFF;
		else
		{
			map[i].clr = ft_atoi_base(ft_strchr(nums[i], ',') + 3, 16);
		}
		free(nums[i]);
	}
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
		fill_matrix(data->map[i], line);
		free(line);
	}
	line = get_next_line(fd);
	free(line);
	close(fd);
	data->map[i] = NULL;
	//ft_print_imatrix(data->map, data->height, data->width);
}
