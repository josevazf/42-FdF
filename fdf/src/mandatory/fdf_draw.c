/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:31:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/10/09 21:52:22 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_int_max(int x, int y)
{
	if (x >= y)
		return (x);
	else
		return (y);
}

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));

	*((unsigned int *)(offset + img->mlx_pixel_addr)) = color;
}

void	set_coordinates(t_data *data)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	spc_width = (WINDOW_WIDTH - 100) / (data->width - 1);
	spc_height = (WINDOW_HEIGHT - 100) / (data->height - 1);
	if (spc_height * data->height > WINDOW_HEIGHT)
		spacing = spc_width;
	else
		spacing = spc_height;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
				data->map[i][j].x = 50 + (j * spacing);
				data->map[i][j].y = 50 + (i * spacing);
		}
	}
}

void	color_screen(t_data *data, int color)
{
	int spc_height;
	int spc_width;
	int spacing;
	int i;
	int j;
	
	i = -1;
	j = -1;
	set_coordinates(data);
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (data->map[i][j].z == 0)
				ft_pixel_put(&data->img, data->map[i][j].x, data->map[i][j].y, color);
			else
				ft_pixel_put(&data->img, data->map[i][j].x, data->map[i][j].y, data->map[i][j].clr);
		}
	}
	draw_lines(data->map[0][0].x, data->map[0][0].y, data->map[0][1].x, data->map[0][1].y, data);
}

void	draw_lines(int x1, int y1, int x2, int y2, t_data *data)
{
    // Iterators, counters required by algorithm
    int x;
	int y;
	int dx;
	int dy;
	int dx1;
	int dy1;
	int px;
	int py;
	int xe;
	int ye;
	int i;
    // Calculate line deltas
    dx = x2 - x1;
    dy = y2 - y1;
    // Create a positive copy of deltas (makes iterating easier)
    dx1 = abs(dx);
    dy1 = abs(dy);
    // Calculate error intervals for both axis
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    // The line is X-axis dominant
    if (dy1 <= dx1) {
        // Line is drawn left to right
        if (dx >= 0) {
            x = x1; y = y1; xe = x2;
        } else { // Line is drawn right to left (swap ends)
            x = x2; y = y2; xe = x1;
        }
        ft_pixel_put(&data->img, x, y, CLR_FLAMINGO); // Draw first pixel
        // Rasterize the line
        for (i = 0; x < xe; i++) {
            x = x + 1;
            // Deal with octants...
            if (px < 0) {
                px = px + 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
            // Draw pixel from line span at
            // currently rasterized position
            ft_pixel_put(&data->img, x, y, CLR_FLAMINGO);
        }
    } else { // The line is Y-axis dominant
        // Line is drawn bottom to top
        if (dy >= 0) {
            x = x1; y = y1; ye = y2;
        } else { // Line is drawn top to bottom
            x = x2; y = y2; ye = y1;
        }
		ft_pixel_put(&data->img, x, y, CLR_FLAMINGO); // Draw first pixel
        // Rasterize the line
        for (i = 0; y < ye; i++) {
            y = y + 1;
            // Deal with octants...
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
            // Draw pixel from line span at
            // currently rasterized position
			ft_pixel_put(&data->img, x, y, CLR_FLAMINGO); 
        }
    }
 }
 