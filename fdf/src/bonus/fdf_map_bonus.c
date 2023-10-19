/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:27:29 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/19 19:47:35 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Get Z max and min values */
void	get_maxmin(t_data *data, int val)
{
	if (val >= data->z_max)
		data->z_max = val;
	else if (val <= data->z_min)
		data->z_min = val;
}

/* Get dimensions of the map, w (width) and h (height)*/
void	get_dimensions(char *file_name, t_data *data)
{
	int		fd;
	char	*line;

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
		if (data->w == 0)
			data->w = ft_count_words(line);
		data->h++;
		free(line);
	}
	close(fd);
}

/* Create an empty matrix representation of the map */
void	create_map(t_data *data)
{
	int	i;

	i = -1;
	data->map = (t_point **)malloc(sizeof(t_point *) * (data->h + 1));
	malloc_error(data->map);	
	while (++i < data->h)
	{
		data->map[i] = (t_point *)malloc(sizeof(t_point) * (data->w + 1));
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
		get_maxmin(data, map[i].z);
		if (!ft_strchr(nums[i], ','))
			map[i].clr = CLR_WHITE;
		else
		{
			map[i].clr = ft_atoi_base(ft_strchr(nums[i], ',') + 3, 16);
			data->flag_col = 0;
		}
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
	fd = open(file_name, O_RDONLY, 0);
	fd_error(fd);
	create_map(data);
	while (++i < data->h)
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
