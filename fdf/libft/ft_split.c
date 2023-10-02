/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:01:33 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/02 17:48:21 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns an array of strings obtained by splitting ’s’ using the
   character ’c’ as a delimiter. */

#include "libft.h"

static char	*ft_strposi(char const *s, char c, int pos)
{
	size_t	i;
	char	*subs;

	i = pos;
	while (s[i] != '\0' && s[i] != c)
		i++;
	subs = ft_substr(s, pos, (i - pos));
	return (subs);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		i;
	int		j;

	i = 0;
	j = -1;
	out = malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			out[++j] = ft_strposi(s, c, i);
			i = i + ft_strlen(out[j]);
		}
	}
	out[++j] = NULL;
	return (out);
}
