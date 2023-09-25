/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:41:54 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/25 19:44:39 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

//! this function is used to change player angle
void	change_angle(t_cub3D *cb, int KEY)
{
	if (KEY == MLX_KEY_RIGHT)
		cb->angle += ANGLE_MOV;
	else if (KEY == MLX_KEY_LEFT)
		cb->angle -= ANGLE_MOV;
	if (cb->angle < 0)
		cb->angle += 2 * M_PI;
	if (cb->angle > 2 * M_PI)
		cb->angle -= 2 * M_PI;
}

void	move_player(t_cub3D *cb, double x, double y)
{
	int	marge_x;
	int	marge_y;
	int	next_x;
	int	next_y;

	x *= SPEED;
	y *= SPEED;
	next_x = (int)x;
	next_y = (int)y;
	marge_x = 15;
	marge_y = 15;
	if (next_x < 0)
		marge_x *= -1;
	if (y < 0)
		marge_y *= -1;
	if (cb->map.map_tmp[(cb->player.y + next_y + marge_y) / TILE_SIZE]
		[cb->player.x / TILE_SIZE] != '1')
		cb->player.y += next_y;
	if (cb->map.map_tmp[cb->player.y / TILE_SIZE]
		[(cb->player.x + next_x + marge_x) / TILE_SIZE] != '1')
		cb->player.x += next_x;
}

//! this function for key hook so every key do action functionality
void	ft_hook(void *param)
{
	t_cub3D	*cb;

	cb = param;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cb->mlx);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		change_angle(cb, MLX_KEY_LEFT);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
		change_angle(cb, MLX_KEY_RIGHT);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_W))
		move_player(cb, cos(cb->angle), sin(cb->angle));
	if (mlx_is_key_down(cb->mlx, MLX_KEY_S))
		move_player(cb, -cos(cb->angle), -sin(cb->angle));
	if (mlx_is_key_down(cb->mlx, MLX_KEY_A))
		move_player(cb, -cos(cb->angle + (M_PI / 2)),
			-sin(cb->angle + (M_PI / 2)));
	if (mlx_is_key_down(cb->mlx, MLX_KEY_D))
		move_player(cb, cos(cb->angle + (M_PI / 2)),
			sin(cb->angle + (M_PI / 2)));
}
