/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/23 14:45:36 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
//! this function is used to change player angle
void change_angle(t_cube3d *cb, int KEY)
{
	if (KEY == MLX_KEY_LEFT)
		cb->angle -= 10;
	else if (KEY == MLX_KEY_RIGHT)
		cb->angle += 10;
}
//! this function to change player position
void change_player(t_cube3d *cb, int KEY)
{
	if (KEY == MLX_KEY_A)
		cb->player.x -= 8;
	else if (KEY == MLX_KEY_D)
		cb->player.x += 8;
	else if (KEY == MLX_KEY_W)
		cb->player.y -= 8;
	else if (KEY == MLX_KEY_S)
		cb->player.y += 8;
}

//! i didn't uset because it print ligne but i can't move it around 
void mlx_draw_line(mlx_t *mlx, int x1, int y1, int x2, int y2, uint32_t color)
{
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;
	mlx_image_t *img;

	img = mlx_new_image(mlx, 2500, 1300);
	mlx_put_pixel(img, x1, y1, color);
	while (x1 != x2 && y1 != y2)
	{
		mlx_put_pixel(img, x1, y1, color);
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
	mlx_image_to_window(mlx, img, 0, 0);
}

void draw_player(t_cube3d *cb, int angle, int playerSize)
{
    int i;
    int j;
	int x;
	int y;
    int centerX = cb->player.x - COF_PIXEL/2;
    int centerY = cb->player.y;

	angle += 90; //for ajustement
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
            angleDifference = fmin(angleDifference, 360 - angleDifference);

            // Check if the point is within the desired shape
            if (distance <= playerSize && angleDifference <= 45)
            {
                mlx_put_pixel(cb->img, x, y + COF_PIXEL/2, cb->p_color);
            }
        }
    }

    mlx_image_to_window(cb->mlx, cb->img, 0, 0);
}

void draw_map(t_cube3d *cb)
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
						mlx_put_pixel(cb->img, x * COF_PIXEL + i, y * COF_PIXEL + j, cb->color);
					else if (cb->map.map_tmp[y][x] == 'N')
					{
						mlx_put_pixel(cb->img, x * COF_PIXEL + i, y * COF_PIXEL + j, cb->color);
						// mlx_put_pixel(img, x * COF_PIXEL + i, y * COF_PIXEL + j, z_color);
						// mlx_put_pixel(cb->img, x * COF_PIXEL + (COF_PIXEL / 2), y * COF_PIXEL + (COF_PIXEL / 2), p_color);
					}
					else if (cb->map.map_tmp[y][x] == '0') 
						mlx_put_pixel(cb->img, x * COF_PIXEL + i, y * COF_PIXEL + j, cb->z_color);
				}
			}
		}
	}
	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
}

//! this function for key hook so every key do action functionality
void ft_hook(void* param)
{
	t_cube3d  *cb = param;

	if (mlx_is_key_down(cb->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cb->mlx);
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_UP))
		{

			// mlx_draw_line(mlx, 0, 0, 100, 100, ft_pixel(0x00, 0x00, 0x00, 0x00));			
			printf("up\n");
		}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_DOWN))
		printf("down\n");
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		{
			printf("left\n");
			change_angle(cb, MLX_KEY_LEFT);
		}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
	{
		printf("right\n");
		change_angle(cb, MLX_KEY_RIGHT);
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_W))
	{
		change_player(cb, MLX_KEY_W);
		printf("w\n");
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_S))
	{
		change_player(cb, MLX_KEY_S);
		printf("s\n");
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_A))
	{
		change_player(cb, MLX_KEY_A);
		printf("a\n");
	}
	else if(mlx_is_key_down(cb->mlx, MLX_KEY_D))
	{
		change_player(cb, MLX_KEY_D);
		printf("d\n");
	}	
		// mlx_close_window(mlx);
	draw_map(cb);
	draw_player(cb, cb->angle, COF_PIXEL/2);
}

// void draw_player(t_cube3d *cb)
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


void    testing(t_cube3d *cb)
{
	mlx_t			*mlx;
	mlx_image_t		*img;

	printf("height = %d\n", cb->map.height);
	printf("width = %d\n", cb->map.width);
	cb->color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	// cb->p_color = ft_pixel(0x00, 0x00, 0x00, 0xFF);
	cb->p_color = ft_pixel(0xFF, 0x00, 0x00, 0xFF);

	// cb->z_color = ft_pixel(0x00, 0x00, 0x00, 0xFF);
	cb->z_color = ft_pixel(0x00, 0xFF, 0xFF, 0xFF);
	mlx = mlx_init(2500, 1300 , "cub3D", false);
	// change cb->mlx to mlx and cb->img to img
	cb->mlx = mlx;
	img = mlx_new_image(mlx, 2500, 1300);
	cb->img = img;
	draw_map(cb);
	draw_player(cb, cb->angle, COF_PIXEL/2);
	// mlx->win = mlx_new_window(mlx, 2500, 1300, "cub3D");
	
	mlx_loop_hook(mlx, ft_hook, cb);
	mlx_loop(mlx);
}

/*####  function are in validation dir  #####*/
int main(int ac, char **av)
{
	t_cube3d cb;

	if (ac != 2)
		handl_errors(10);
	init_cube3d(&cb);
	cb.fd = open(av[1], O_RDONLY);
	if (cb.fd == -1 || check_parameters(av[1]) == 0 || check_content(&cb))
		handl_errors(6);


	testing(&cb);
	// int y;
	// for (y = 0; cb.map.map_tmp[y]; y++)
	// 	for (int x = 0; cb.map.map_tmp[y][x]; x++)
	// 		cb.map.map[y][x] = cb.map.map_tmp[y][x];
	// 	*cb.map.map[y] = '\0';
	// ft_free_double(cb.map.map_tmp);
	// for (int g = 0; *cb.map.map[g]; g++)
	// 	print(cb.map.map[g], 0);
	// system("leaks cub3D");
	return 0;
}