/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:57:48 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/26 01:25:51 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
//! i didn't uset because it print ligne but i can't move it around 
// void mlx_draw_line(t_cub3D *cb, int x1, int y1, int x2, int y2, uint32_t color)
// {
// 	int dx = abs(x2 - x1);
// 	int sx = x1 < x2 ? 1 : -1;
// 	int dy = abs(y2 - y1);
// 	int sy = y1 < y2 ? 1 : -1;
// 	int err = (dx > dy ? dx : -dy) / 2;
// 	int e2;

// 	mlx_put_pixel(cb->img, x1, y1, color);
// 	while (x1 != x2 && y1 != y2)
// 	{
// 		mlx_put_pixel(cb->img, x1, y1, color);
// 		e2 = err;
// 		if (e2 > -dx)
// 		{
// 			err -= dy;
// 			x1 += sx;
// 		}
// 		if (e2 < dy)
// 		{
// 			err += dx;
// 			y1 += sy;
// 		}
// 	}
// }

int is_wall_pixel(t_cub3D *cb, float x, float y)
{
		// printf("the map is %c\n",cb->map.map_tmp[(int)y/COF_PIXEL][(int)x/COF_PIXEL]);
	if (cb->map.map_tmp[(int)y/COF_PIXEL][(int)x/COF_PIXEL] == '1')
	{
		return (0);
	}
	return (1);
}

int check_wall(t_cub3D *cb)
{
	if (cb->map.map_tmp[(int)((cb->player.y + COF_PIXEL/2)/COF_PIXEL)][(int)((cb->player.x + COF_PIXEL/2)/COF_PIXEL)] == '1')
		return (0);
	// 	return (1);
	return (1);
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

int	if_player(char c)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void draw_map(t_cub3D *cb)
{
	int				x;
	int				y;
	int				i;
	int				j;

	y = -1;
	// for (int g = 0; cb->map.map_tmp[g]; g++)
	// 	print(cb->map.map_tmp[g], 0);
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

//! this function is used to change player angle
void change_angle(t_cub3D *cb, int KEY)
{
	if (KEY == MLX_KEY_RIGHT && (cb->angle)%360 <= 170)
		cb->angle = (cb->angle + 10)%350;
	else if (KEY ==  MLX_KEY_LEFT && cb->angle >= -170)
		cb->angle = (cb->angle - 10)%350;
	else if (cb->angle == 180 && KEY == MLX_KEY_RIGHT)
		cb->angle = -170;
	else
		cb->angle = 170;
}

//! this function to change player position
void change_player(t_cub3D *cb, int KEY)
{
	float next_x;
	float next_y;
	if (KEY == MLX_KEY_S)
	{
		next_x = cb->player.x + (cos(cb->angle * M_PI / 180) * 4);
		next_y = cb->player.y + (sin(cb->angle * M_PI / 180) * 4);
		if (is_wall_pixel(cb,next_x, next_y))
		{
			cb->player.x = next_x;
            cb->player.y = next_y;
		}
		// printf("the angle is %d in w and cos %f\n", cb->angle,cos(cb->angle * M_PI / 180));
	}
	else if (KEY == MLX_KEY_A && is_wall_pixel(cb, cb->player.x, cb->player.y))
	{
		next_x = cb->player.x + cos((90 - cb->angle) * M_PI / 180) * 4;
		next_y = cb->player.y + sin((90 - cb->angle) * M_PI / 180) * 4;
		if(is_wall_pixel(cb,next_x, next_y))
		{
			cb->player.x = next_x;
			cb->player.y = next_y;
		}
		// printf("the angle is %d in d\n", cb->angle);
		// printf("map x is %d, and y is %d\n",(cb->player.x/COF_PIXEL),(cb->player.y/COF_PIXEL));

	}
	else if (KEY == MLX_KEY_D && is_wall_pixel(cb, cb->player.x, cb->player.y))
	{
		next_x = cb->player.x - cos((90 - cb->angle) * M_PI / 180) * 4;
		next_y = cb->player.y - sin((90 - cb->angle) * M_PI / 180) * 4;
		if(is_wall_pixel(cb,next_x, next_y))
		{
			cb->player.x = next_x;
			cb->player.y = next_y;
		}
		// printf("the angle is %d in a\n", cb->angle);

	}
	else if (KEY == MLX_KEY_W && is_wall_pixel(cb, cb->player.x, cb->player.y))
	{
		next_x = cb->player.x - cos(cb->angle * M_PI / 180) * 4;
		next_y = cb->player.y - sin(cb->angle * M_PI / 180) * 4;
		if(is_wall_pixel(cb, next_x, next_y))
		{
			cb->player.x = next_x;
            cb->player.y = next_y;
		}
		// printf("the angle is %d in s\n", cb->angle);
	}
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