/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:57:48 by yaidriss          #+#    #+#             */
/*   Updated: 2023/10/05 14:43:56 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_wall_pixel(t_cub3D *cb, double x, double y)
{
	int	pos_y;
	int	pos_x;

	if (y / T_S < 1 || x / T_S < 1
		|| y / T_S > cb->map.height - 1
		|| x / T_S > cb->map.width - 1)
		return (0);
	pos_y = y / T_S;
	pos_x = x / T_S;
	if (pos_x < 0 || pos_y < 0
		|| pos_x > cb->map.width || pos_y > cb->map.height)
		return (0);
	if (cb->map.map_tmp[pos_y][pos_x] == '1')
		return (0);
	return (1);
}

double angle_overlap(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
