/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/24 16:12:44 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void draw_player(t_cub3D *cb, int angle, int playerSize)
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
            int angleDifference = abs(angle- (int)pointAngle);
            angleDifference = fmin(angleDifference, 360 - angleDifference);

            // Check if the point is within the desired shape
            if (distance <= playerSize && angleDifference <= 45)
            {
                mlx_put_pixel(cb->img, x, y + COF_PIXEL/2, 0xFF0000FF);
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
	if (KEY == MLX_KEY_LEFT)
		cb->angle -= 10;
	else if (KEY == MLX_KEY_RIGHT)
		cb->angle += 10;
}

//! this function to change player position
void change_player(t_cub3D *cb, int KEY)
{
	// cb->player.x += cos(cb->angle - 
	if (KEY == MLX_KEY_A)
	{
		cb->player.x += cos(cb->angle - M_PI / 2.0) * 4;
		cb->player.y += sin(cb->angle - M_PI / 2.0) * 4;
	}
	else if (KEY == MLX_KEY_D)
	{
		cb->player.x -= cos(cb->angle - M_PI / 2.0) * 4;
		cb->player.y -= sin(cb->angle - M_PI / 2.0) * 4;
	}
	else if (KEY == MLX_KEY_W)
	{
		cb->player.x += cos(cb->angle) * 4;
		cb->player.y += sin(cb->angle) * 4;
	}
	else if (KEY == MLX_KEY_S)
	{
		cb->player.x -= cos(cb->angle) * 4;
		cb->player.y -= sin(cb->angle) * 4;
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

//! this function for key hook so every key do action functionality
void ft_hook(void* param)
{
	t_cub3D  *cb = param;

	if (mlx_is_key_down(cb->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cb->mlx);
	// else if(mlx_is_key_down(cb->mlx, MLX_KEY_UP))
	// 	{

	// 		// mlx_draw_line(cb, 0, 0, 100, 100, 0x00FF00FF);			
	// 		// printf("up\n");
	// 	}
	// else if(mlx_is_key_down(cb->mlx, MLX_KEY_DOWN))
	// 	// printf("down\n");
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
	{
		// printf("left\n");
		change_angle(cb, MLX_KEY_LEFT);
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
	{
		// printf("right\n");
		change_angle(cb, MLX_KEY_RIGHT);
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_W))
	{
		change_player(cb, MLX_KEY_W);
		// printf("w\n");
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_S))
	{
		change_player(cb, MLX_KEY_S);
		// printf("s\n");
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_A))
	{
		change_player(cb, MLX_KEY_A);
		// printf("a\n");
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_D))
	{
		change_player(cb, MLX_KEY_D);
		// printf("d\n");
	}	
		// mlx_close_window(mlx);
	draw_C_F(cb);
	draw_map(cb);
	draw_player(cb, cb->angle, COF_PIXEL / 2);
}

// void draw_player(t_cub3D *cb)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	j = -1;
// 	while(++i < COF_PIXEL)
// 	{
// 		j= 0;
// 		while(++j < COF_PIXEL)
// 		{
// 			if((i - j)*(i - j) < COF_PIXEL/2)
// 				mlx_put_pixel(cb->img, cb->player.x*COF_PIXEL + i, cb->player.y*COF_PIXEL + j,cb->p_color);
// 		}
// 	}
// 	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
// }

void    testing(t_cub3D *cb)
{
	// printf("height = %d\n", cb->map.height);
	// printf("width = %d\n", cb->map.width);
	cb->mlx = mlx_init(2500, 1300 , "cub3D", false);
	cb->img = mlx_new_image(cb->mlx, 2500, 1300);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
	// draw_player(cb, cb->angle, COF_PIXEL/2);
	// draw_map(cb);
	// mlx->win = mlx_new_window(mlx, 2500, 1300, "cub3D");
	
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop(cb->mlx);
}

int main(int ac, char **av)
{
	t_cub3D cb;

	if (ac != 2)
		handl_errors(10);
	init_cub3D(&cb);
	cb.fd = open(av[1], O_RDONLY);
	if (cb.fd == -1 || check_parameters(av[1]) == 0 || check_content(&cb))
		handl_errors(6);
	testing(&cb);

	
// for (int g = 0; cb.map.map_tmp[g]; g++)
// 		print(cb.map.map_tmp[g], 0);

//copy maptmp to stack map but its not good 
	// int a;
	// int b;
	// int x;
	// int y;
	// int tmp;
	// int tmp2;
	
	// y = 0;
	// a = 0;
	// tmp = COF_PIXEL;
	// tmp2 = 5;//nbr row
	// while (cb.map.map_tmp[y])
	// {
	// 	while (a < tmp2)
	// 	{
	// 		x = 0;
	// 		b = 0;
	// 		tmp = COF_PIXEL;
	// 		while (cb.map.map_tmp[y][x])
	// 		{
	// 			while (b < tmp)
	// 				cb.map.map[a][b++] = cb.map.map_tmp[y][x];
	// 			x++;
	// 			tmp += COF_PIXEL;
	// 		}
	// 		cb.map.map[a][b] = '\0';
	// 		a++;
	// 	}
	// 	tmp2 += 5;
	// 	y++;
	// }
	// *cb.map.map[a] = '\0';
	// ft_free_double(cb.map.map_tmp);
	// for (int g = 0; cb.map.map_tmp[g]; g++)
	// 	print(cb.map.map_tmp[g], 0);
	// system("leaks cub3D");
	return 0;
}