/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/03 11:27:53 by jrocha-v         ###   ########.fr       */
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
    int     height;
    int     width;
    int     **altitude;
    
    void    *mlx_ptr;
    void    *win_ptr;

}   fdf_init;

// fdf_main.c

// fdf_read_map.c
void	read_file(char *file_name, fdf_init *data);
int		get_height(char *file_name);
int		get_width(char *file_name);
void	fill_matrix(int *altitude, char *line);

// fdf_events.c
int		press_key(int key, void *param);

#endif
