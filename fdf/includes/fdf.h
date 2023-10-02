/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/09/29 18:35:44 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# define SUCCESS 0
# define ERROR 1

# define WINDOW_WIDTH 900
# define WINDOW_HEIGHT 600

# define ESC 65307

# define RED_PIXEL 0xFF0000

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;

}   t_data;

// fdf_main.c
int		deal_key(int key, void *param);

#endif
