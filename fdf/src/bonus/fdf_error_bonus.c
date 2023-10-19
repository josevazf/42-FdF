/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:51 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/19 19:07:03 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

/* Free the map matrix */
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
