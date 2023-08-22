/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/23 00:15:36 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void    testing(t_cube3d *cb)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				x;
	int				y;
	int				i;
	int				j;

	printf("height = %d\n", cb->map.height);
	printf("width = %d\n", cb->map.width);
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	uint32_t p_color = ft_pixel(0x00, 0xFF, 0x00, 0xFF);
	mlx = mlx_init(cb->map.height * COF_PIXEL, cb->map.width * COF_PIXEL , "cub3D", false); 
	img = mlx_new_image(mlx, cb->map.height * COF_PIXEL, cb->map.width * COF_PIXEL);

	y = -1;
	while (cb->map.map_tmp[++y])
	{
		x = -1;
		while (cb->map.map_tmp[y][++x])
		{
			j = -1;
			while (++j < COF_PIXEL)
			{
				i = -1;
				while (++i < COF_PIXEL)
				{
					if (cb->map.map_tmp[y][x] == '1') 
						mlx_put_pixel(img, x * 50 + i, y * 50 + j, color);
					else if (cb->map.map_tmp[y][x] == 'N')
						mlx_put_pixel(img, x * 50 + 25, y * 50 + 25, p_color);
				}
			}
		}
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
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

	for (int g = 0; cb.map.map_tmp[g]; g++)
		print(cb.map.map_tmp[g], 0);

	testing(&cb);
	
	// system("leaks cub3D");
	return 0;
}