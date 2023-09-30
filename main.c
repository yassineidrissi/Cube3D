/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/30 11:00:32 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start_mlx(t_cub3D *cb)
{
	cb->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT , "cub3D", false);
	cb->img = mlx_new_image(cb->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cb->img2 = mlx_new_image(cb->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
	mlx_image_to_window(cb->mlx, cb->img2, 0, 0);
	// map(cb);
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop_hook(cb->mlx, main_work, cb);
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
	if (cb.fd == -1 || check_parameters(av[1]) || check_content(&cb))
	{
		close(cb.fd);
		handl_errors(6);
	}
	start_mlx(&cb);
	// system("leaks -q cub3D");
	return (0);
}