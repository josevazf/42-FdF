/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:51 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/18 17:15:30 by jrocha-v         ###   ########.fr       */
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
