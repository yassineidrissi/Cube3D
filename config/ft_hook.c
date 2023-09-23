/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:41:54 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/23 10:07:53 by zouaraqa         ###   ########.fr       */
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

void	move_player(t_cub3D *cb, double rad_angle)
{
	int	next_x;
	int	next_y;
	int	marge_x;
	int	marge_y;

	marge_x = 20;
	marge_y = 20;
	next_x = cb->player.x + (cos(rad_angle) * SPEED);
	next_y = cb->player.y + (sin(rad_angle) * SPEED);
	if (next_x < 0)
		marge_x *= -1;
	if (marge_y < 0)
		next_y *= -1;
	if (cb->map.map_tmp[(int)(next_y + marge_y) / COF_PIXEL]
		[(int)cb->player.x / COF_PIXEL] != '1')
		cb->player.y = next_y;
	if (cb->map.map_tmp[(int)cb->player.y / COF_PIXEL]
		[(int)(next_x + marge_x) / COF_PIXEL] != '1')
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
		move_player(cb, cb->angle);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_S))
		move_player(cb, (cb->angle + M_PI));
	if (mlx_is_key_down(cb->mlx, MLX_KEY_A))
		move_player(cb, (cb->angle - (M_PI / 2)));
	if (mlx_is_key_down(cb->mlx, MLX_KEY_D))
		move_player(cb, (cb->angle + (M_PI / 2)));
}
