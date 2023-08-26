/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:57:48 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/26 11:51:22 by zouaraqa         ###   ########.fr       */
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


// int check_wall(t_cub3D *cb)
// {
// 	if (cb->map.map_tmp[(int)((cb->player.y + COF_PIXEL/2)/COF_PIXEL)][(int)((cb->player.x + COF_PIXEL/2)/COF_PIXEL)] == '1')
// 		return (0);
// 	// 	return (1);
// 	return (1);
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
	if (KEY == MLX_KEY_W)
	{
		next_x = cb->player.x + cos(cb->angle * M_PI / 180) * 4;
		next_y = cb->player.y + sin(cb->angle * M_PI / 180) * 4;
		if(is_wall_pixel(cb, next_x, next_y))
		{
			cb->player.x = next_x;
            cb->player.y = next_y;
		}
		// printf("the angle is %d in s\n", cb->angle);
		printf("the map is %c\n",cb->map.map_tmp[(int)next_y/COF_PIXEL][(int)next_x/COF_PIXEL]);
	}
	else if (KEY == MLX_KEY_S)
	{
		next_x = cb->player.x - (cos(cb->angle * M_PI / 180) * 4);
		next_y = cb->player.y - (sin(cb->angle * M_PI / 180) * 4);
		if (is_wall_pixel(cb,next_x, next_y))
		{
			cb->player.x = next_x;
            cb->player.y = next_y;
		}
		printf("the map is %c\n",cb->map.map_tmp[(int)next_y/COF_PIXEL][(int)next_x/COF_PIXEL]);
		// printf("the angle is %d in w and cos %f\n", cb->angle,cos(cb->angle * M_PI / 180));
	}
	else if (KEY == MLX_KEY_A)
	{
		next_x = cb->player.x + cos((90 - cb->angle) * M_PI / 180) * 4;
		next_y = cb->player.y + sin((-90 - cb->angle) * M_PI / 180) * 4;
		if(is_wall_pixel(cb,next_x, next_y))
		{
			cb->player.x = next_x;
			cb->player.y = next_y;
		}
		// printf("the angle is %d in d\n", cb->angle);
		printf("the map is %c\n",cb->map.map_tmp[(int)next_y/COF_PIXEL][(int)next_x/COF_PIXEL]);
		// printf("map x is %d, and y is %d\n",(cb->player.x/COF_PIXEL),(cb->player.y/COF_PIXEL));
	}
	else if (KEY == MLX_KEY_D)
	{
		next_x = cb->player.x - cos((90 - cb->angle) * M_PI / 180) * 4;
		next_y = cb->player.y - sin((-90 - cb->angle) * M_PI / 180) * 4;
		if(is_wall_pixel(cb,next_x, next_y))
		{
			cb->player.x = next_x;
			cb->player.y = next_y;
		}
		// printf("the angle is %d in a\n", cb->angle);
		printf("the map is %c\n",cb->map.map_tmp[(int)next_y/COF_PIXEL][(int)next_x/COF_PIXEL]);
	}
}

//! this function for key hook so every key do action functionality
void ft_hook(void* param)
{
	t_cub3D  *cb = param;

	if (mlx_is_key_down(cb->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cb->mlx);
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		change_angle(cb, MLX_KEY_LEFT);
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
		change_angle(cb, MLX_KEY_RIGHT);
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_W))
		change_player(cb, MLX_KEY_W);
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_S))
		change_player(cb, MLX_KEY_S);
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_A))
		change_player(cb, MLX_KEY_A);
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_D))
		change_player(cb, MLX_KEY_D);
	// else if(mlx_is_key_down(cb->mlx, MLX_KEY_UP))
	// 	{

	// 		mlx_draw_line(cb, 0, 0, 100, 100, 0xFF0000FF);			
	// 		// printf("up\n");
	// 	}
	// mlx_close_window(mlx);
	draw_C_F(cb);
	draw_map(cb);
	draw_player(cb, cb->angle, COF_PIXEL / 2, AGNGLE_VUE);
}
