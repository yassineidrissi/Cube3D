/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/26 00:00:02 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	draw_player(cb, cb->angle, COF_PIXEL / 2, AGNGLE_VUE);
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