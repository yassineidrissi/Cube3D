/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:57:48 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/27 16:15:49 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void mlx_draw_line(t_cub3D *cb, int x1, int y1, int x2, int y2, uint32_t color)
{
	if (x2 < 0  || y2 < 0)
		return;
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;
	mlx_put_pixel(cb->img, x1, y1, color);
	while (x1 != x2 && y1 != y2)
	{
		mlx_put_pixel(cb->img, x1, y1, color);
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void draw_line(mlx_image_t *img, int start_x, int start_y, int end_x, int end_y, size_t color)
{
    int x0 = start_x;
    int y0 = start_y;
    int x1 = end_x;
    int y1 = end_y;
    int x = x0;
    int y = y0;

    int dx1 = abs(x1 - x0);
    int dy1 = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx1 - dy1;

    while (x != x1 || y != y1)
    {
        mlx_put_pixel(img, x, y, color);
        int e2 = 2 * err;
        if (e2 > -dy1)
        {
            err -= dy1;
            x += sx;
        }
        if (e2 < dx1)
        {
            err += dx1;
            y += sy;
        }
    }
}

int is_wall_pixel(t_cub3D *cb, double x, double y)
{
	int pos_y;
	int pos_x;

	if (y / TILE_SIZE  < 1 || x / TILE_SIZE < 1
		|| y / TILE_SIZE > cb->map.height - 1 || x / TILE_SIZE  > cb->map.width - 1)
		return (0);
	
	pos_y = y / TILE_SIZE;
	pos_x = x / TILE_SIZE;
	if (pos_x < 0 || pos_y < 0 || pos_x > cb->map.width || pos_y > cb->map.height)
	{
		printf("we out of maps and x is %d and y is %d\n", pos_x, pos_y);		
		return (0);
	}
	if (cb->map.map_tmp[pos_y][pos_x] == '1')
		return (0);
	return (1);
}