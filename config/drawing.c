/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:38:15 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/29 11:08:00 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	if_player(char c)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_c_f(t_cub3D *cb)
{
	uint32_t	color_c;
	uint32_t	color_f;
	int			x;
	int			y;

	y = -1;
	color_c = ft_pixel(cb->colors[C].r, cb->colors[C].g, cb->colors[C].b, 255);
	color_f = ft_pixel(cb->colors[F].r, cb->colors[F].g, cb->colors[F].b, 255);
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				mlx_put_pixel(cb->img, x, y, color_c);
			else if (y >= WINDOW_HEIGHT / 2)
				mlx_put_pixel(cb->img, x, y, color_f);
		}
	}
}

void	draw_map(t_cub3D *cb)
{
	cb->ts = (T_S / 16);
	cb->y = -1;
	while (cb->map.map_tmp[++cb->y])
	{
		cb->x = -1;
		while (cb->map.map_tmp[cb->y][++cb->x])
		{
			cb->j = -1;
			while (++cb->j < (T_S / cb->ts))
			{
				cb->i = -1;
				while (++cb->i < (T_S / cb->ts))
				{
					if (cb->map.map_tmp[cb->y][cb->x] == '1') 
						mlx_put_pixel(cb->img2, (cb->x * T_S) / cb->ts + cb->i,
							(cb->y * T_S) / cb->ts + cb->j, 0x00FFFFFF);
					else if (cb->map.map_tmp[cb->y][cb->x] == '0'
						|| if_player(cb->map.map_tmp[cb->y][cb->x]))
						mlx_put_pixel(cb->img2, (cb->x * T_S) / cb->ts + cb->i,
							(cb->y * T_S) / cb->ts + cb->j, 0xFFFFFFFF);
				}
			}
		}
	}
}

void	draw_player(t_cub3D *cb, int playerSize)
{
	double	radians;
	int		angle_vue;
	int		center_x;
	int		center_y;
	int		angle;

	angle = 0;
	center_x = (int)cb->p.x / (T_S / 16);
	center_y = (int)cb->p.y / (T_S / 16);
	while (angle < 360)
	{
		radians = (angle + angle_vue) * (M_PI / 180.0);
		cb->x = center_x + (int)(playerSize * cos(radians));
		cb->y = center_y + (int)(playerSize * sin(radians));
		mlx_put_pixel(cb->img2, cb->x, cb->y, 0xFF0000FF);
		angle++;
	}
}
