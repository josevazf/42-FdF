/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:27:29 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/18 16:19:21 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Get dimensions of the map, width and height */
void	get_dimensions(char *file_name, t_data *data)
{
	int		fd;
	char	*line;

	data->height = 0;
	data->width = 0;
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
		if (data->width == 0)
			data->width = ft_count_words(line);
		data->height++;
		free(line);
	}
	close(fd);
}

/* Create an empty matrix representation of the map */
void	create_map(t_data *data)
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

/* Fill the matrix representation of the map with info for each point */
void	fill_map(t_point *map, char *line, t_data *data)
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
		if (map[i].z >= data->z_max)
			data->z_max = map[i].z;
		else if (map[i].z <= data->z_min)
			data->z_min = map[i].z;
		if (!ft_strchr(nums[i], ','))
			map[i].clr = CLR_WHITE;
		else
			map[i].clr = ft_atoi_base(ft_strchr(nums[i], ',') + 3, 16);
		free(nums[i]);
	}

	free(nums);
}

/* Get all map info */
void	process_map(char *file_name, t_data *data)
{
	char	*line;
	int 	i;
	int 	fd;

	i = -1;
	get_dimensions(file_name, data);
	data->z_max = 0;
	data->z_min = 0;
	fd = open(file_name, O_RDONLY, 0);
	fd_error(fd);
	create_map(data);
	while (++i < data->height)
	{
		line = get_next_line(fd);
		fill_map(data->map[i], line, data);
		free(line);
	}
	data->z_range = data->z_max - data->z_min;
	get_zratio(data);
	printf("%f", data->z_ratio);
	line = get_next_line(fd);
	free(line);
	close(fd);
	data->map[i] = NULL;
}

