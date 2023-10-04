/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_imatrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:26:21 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/04 12:01:18 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_imatrix(int **matrix)
{
	int i;
	int j;

	i = -1;
	while (matrix[i])
	{
		j = -1;
		while (matrix[i][j])
			ft_printf("%i\t", matrix[i][j]);
		ft_printf("\n");
	}
}