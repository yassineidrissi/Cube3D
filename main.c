/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/23 15:45:57 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	testing(t_cub3D *cb)
{
	cb->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT , "cub3D", false);
	cb->img = mlx_new_image(cb->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cb->img2 = mlx_new_image(cb->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
	mlx_image_to_window(cb->mlx, cb->img2, 0, 0);
	// map(cb);
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop_hook(cb->mlx, test, cb);
	// mlx_loop_hook(cb->mlx, map, cb);
	mlx_loop(cb->mlx);
}

int main(int ac, char **av)
{
	t_cub3D cb;

	if (ac != 2)
		handl_errors(10);
	init_cub3d(&cb);
	cb.fd = open(av[1], O_RDONLY);
	if (cb.fd == -1 || check_parameters(av[1]) == 0 || check_content(&cb))
		handl_errors(6);
	testing(&cb);
	return (0);
}