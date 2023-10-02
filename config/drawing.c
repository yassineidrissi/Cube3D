/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:38:15 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/10/02 12:17:56 by zouaraqa         ###   ########.fr       */
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
