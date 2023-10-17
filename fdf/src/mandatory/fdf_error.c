/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:51 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/17 12:46:56 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	malloc_error(void* input)
{
	if (input == NULL)
		ft_error("fdf: malloc failed", ERROR);
	return (SUCCESS);
}

int	fd_error(int fd)
{
	if (fd == -1)
		ft_error("fdf: file error", ERROR);
	return (SUCCESS);
}

int	args_error(void)
{
	ft_printf("fdf usage: ./fdf map_name.fdf\n");
	exit (ERROR);
}

int	map_error(t_data *data)
{
	ft_free_map(data->map);
	ft_printf("fdf usage: map is not defined by numbers only\n");
	exit (ERROR);
}
