/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:38:15 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/28 15:06:44 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	if_player(char c)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_C_F(t_cub3D *cb)
{
	uint32_t	color_C;
	uint32_t	color_F;
	int			x;
	int			y;

	y = -1;
	color_C = ft_pixel(cb->colors[C].r, cb->colors[C].g, cb->colors[C].b, 255);
	color_F = ft_pixel(cb->colors[F].r, cb->colors[F].g, cb->colors[F].b, 255);
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				mlx_put_pixel(cb->img, x, y, color_C);
			else if (y >= WINDOW_HEIGHT / 2)
				mlx_put_pixel(cb->img, x, y, color_F);
		}
	}
}

void draw_map(t_cub3D *cb)
{
	int				x;
	int				y;
	int				i;
	int				j;

	y = -1;
	while (cb->map.map_tmp[++y])
	{
		x = -1;
		while (cb->map.map_tmp[y][++x])
		{
			j = -1;
			while (++j < (TILE_SIZE / (TILE_SIZE / 16)))
			{
				i = -1;
				while (++i < (TILE_SIZE / (TILE_SIZE / 16)))
				{
					if (cb->map.map_tmp[y][x] == '1') 
						mlx_put_pixel(cb->img2, (x  * TILE_SIZE)/(TILE_SIZE / 16) + i, (y * TILE_SIZE)/(TILE_SIZE / 16) + j, 0x00FFFFFF);
					else if (cb->map.map_tmp[y][x] == '0' || if_player(cb->map.map_tmp[y][x]))
						mlx_put_pixel(cb->img2, (x  * TILE_SIZE)/(TILE_SIZE / 16) + i, (y * TILE_SIZE)/(TILE_SIZE / 16) + j, 0xFFFFFFFF);
				}
			}
		}
	}
}


void draw_player(t_cub3D *cb, int playerSize) 
{
	int angle_vue;
    int centerX = (int)cb->p.x/(TILE_SIZE / 16);
    int centerY = (int)cb->p.y/(TILE_SIZE / 16);
    int radius = playerSize;

    int angle = 0;
    while (angle < 360) 
	{
        double radians = (angle + angle_vue) * (M_PI / 180.0);
        int x = centerX + (int)(radius * cos(radians));
        int y = centerY + (int)(radius * sin(radians));

		mlx_put_pixel(cb->img2, x, y, 0xFF0000FF);
        angle++;
    }

}  
