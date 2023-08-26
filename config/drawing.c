/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:38:15 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/08/26 11:41:44 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	if_player(char c)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

//draw ceiling and floor
void	draw_C_F(t_cub3D *cb)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 1300)
	{
	x = -1;
		while (++x < 2500)
		{
			if (y < 1300 / 2)
				mlx_put_pixel(cb->img, x, y, 0xF005FFF);
			else if (y >= 1300 / 2)
				mlx_put_pixel(cb->img, x, y, 0x0047F0FF);
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
			while (++j < COF_PIXEL - 1)
			{
				i = -1;
				while (++i < COF_PIXEL - 1)
				{
					if (cb->map.map_tmp[y][x] == '1') 
						mlx_put_pixel(cb->img, x  * COF_PIXEL + i, y * COF_PIXEL + j, 0x00FFFFFF);
					else if (cb->map.map_tmp[y][x] == '0' || if_player(cb->map.map_tmp[y][x]))
						mlx_put_pixel(cb->img, x  * COF_PIXEL + i, y * COF_PIXEL + j, 0xFFFFFFFF);
				}
			}
		}
	}
}

void draw_player(t_cub3D *cb, int angle, int playerSize, int angle_vue)
{
    int i;
    int j;
	int x;
	int y;
    int centerX = cb->player.x + COF_PIXEL / 2;
    int centerY = cb->player.y;

	// angle += 90; //for ajustement
    i = -playerSize;
    while (++i <= playerSize)
    {
        j = -playerSize;
        while (++j <= playerSize)
        {
            x = centerX + i;
            y = centerY + j;

            // Calculate distance from center of the player symbol
            int distance = sqrt(i * i + j * j);

            // Calculate angle between the point and player's direction
            float pointAngle = atan2(y - centerY, x - centerX) * 180.0 / PI;
            int angleDifference = abs(angle - (int)pointAngle);
            angleDifference = fmin(angleDifference, 360 - angleDifference) ;

            // Check if the point is within the desired shape
            if (distance <= playerSize && angleDifference <= angle_vue && is_wall_pixel(cb, (float)x,(float)(y + COF_PIXEL/2)))
            {
                // mlx_put_pixel(cb->img, x, y + COF_PIXEL/2, 0xFF0000FF);
				mlx_put_pixel(cb->img, x, y + COF_PIXEL/2, 0xFF000000);
            }
        }
    }
}
