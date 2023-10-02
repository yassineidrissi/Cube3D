/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:51:48 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/10/02 11:33:47 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculate_dis(t_cub3D *cb)
{
	double	dis_h;
	double	dis_v;

	dis_v = sqrt((cb->var.vx - cb->p.x) * (cb->var.vx - cb->p.x)
			+ (cb->var.vy - cb->p.y) * (cb->var.vy - cb->p.y));
	dis_h = sqrt((cb->var.hx - cb->p.x) * (cb->var.hx - cb->p.x)
			+ (cb->var.hy - cb->p.y) * (cb->var.hy - cb->p.y));
	if (dis_h < dis_v)
	{
		cb->var.dis_w = dis_h;
		cb->var.rx = cb->var.hx;
		cb->var.ry = cb->var.hy;
		cb->var.hv = 0;
		cb->var.tx = cb->var.rx;
	}
	else
	{
		cb->var.dis_w = dis_v;
		cb->var.rx = cb->var.vx;
		cb->var.ry = cb->var.vy;
		cb->var.hv = 1;
		cb->var.tx = cb->var.ry;
	}
}

void	put_tx(t_cub3D *cb)
{
	t_putxt	p;

	p.line_lenth = cb->var.line_lenth;
	p.i = cb->var.i;
	p.angle = cb->var.angle;
	p.hv = cb->var.hv;
	p.start_wall = cb->var.start_wall;
	p.tx = cb->var.tx;
	put_texture(cb, &p);
}

void	draw_init(t_cub3D *cb)
{
	draw_c_f(cb);
	cb->var.m_width = cb->map.width * T_S;
	cb->var.m_height = cb->map.height * T_S;
	cb->var.angle = cb->angle - (AGNGLE_VUE / 2 * (M_PI / 180));
	cb->var.angle_step = (AGNGLE_VUE * (M_PI / 180) / WINDOW_WIDTH);
}

int	l_s(t_cub3D *cb)
{
	return (cb->var.angle < (3 * M_PI) / 2 && cb->var.angle > M_PI / 2);
}
