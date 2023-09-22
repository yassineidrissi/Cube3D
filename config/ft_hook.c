/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:41:54 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/22 15:44:58 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

//! this function is used to change player angle
void	change_angle(t_cub3D *cb, int KEY)
{
	if (KEY == MLX_KEY_RIGHT)
	{
		cb->angle += ANGLE_MOV;
		if (cb->angle >= 2 * M_PI)
			cb->angle -= 2 * M_PI;
	}
	else if (KEY == MLX_KEY_LEFT)
	{
		cb->angle -= ANGLE_MOV;
		if (cb->angle < 0)
			cb->angle += 2 * M_PI;
	}
}

void	move_player(t_cub3D *cb, float rad_angle)
{
	int	next_x;
	int	next_y;

	next_x = cb->player.x + (cos(cb->angle - rad_angle) * SPEED);
	next_y = cb->player.y + (sin(cb->angle - rad_angle) * SPEED);
	if (cb->map.map_tmp[(int)next_y / COF_PIXEL]
		[(int)cb->player.x / COF_PIXEL] != '1')
		cb->player.y = next_y;
	if (cb->map.map_tmp[(int)cb->player.y / COF_PIXEL]
		[(int)next_x / COF_PIXEL] != '1')
		cb->player.x = next_x;
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
		move_player(cb, 0);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_S))
		move_player(cb, -M_PI);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_A))
		move_player(cb, (M_PI / 2));
	if (mlx_is_key_down(cb->mlx, MLX_KEY_D))
		move_player(cb, -(M_PI / 2));
}
