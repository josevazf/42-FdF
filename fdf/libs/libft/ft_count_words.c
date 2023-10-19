/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:46:44 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/02 18:53:21 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *str)
{
	int i = 0;
	int count = 0;

	while (str[i])
	{
		while (ft_iswhitespace(str[i]) && str[i])
			i++;
		if (!ft_iswhitespace(str[i]) && str[i])
			count++;
		while (!ft_iswhitespace(str[i]) && str[i])
			i++;
	}
	return (count);
}