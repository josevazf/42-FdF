/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_smatrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:26:21 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/04 12:11:04 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_smatrix(char **matrix)
{
	int i;
	int j;

	i = -1;
	while (matrix[i])
	{
		j = -1;
		while (matrix[i][j])
			ft_printf("%s\t", matrix[i][j]);
		ft_printf("\n");
	}
}