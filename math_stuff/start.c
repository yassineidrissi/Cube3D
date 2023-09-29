/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:46:24 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/29 11:33:12 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	horizontal_block(t_cub3D *cb, int signe, int tile_s)
{
	cb->var.hy = (cb->p.y / T_S) * T_S + tile_s;
	cb->var.hx = cb->p.x + (cb->p.y - cb->var.hy) * cb->var.atan;
	cb->var.hyblock = T_S * signe;
	cb->var.hxblock = -cb->var.hyblock * cb->var.atan;
}

void	vertical_block(t_cub3D *cb, int signe, int tile_s)
{
	cb->var.vx = ((cb->p.x / T_S) * T_S) + tile_s;
	cb->var.vy = cb->p.y + (cb->p.x - cb->var.vx) * cb->var.atan;
	cb->var.vxblock = T_S * signe;
	cb->var.vyblock = -cb->var.vxblock * cb->var.atan;
}

void	add_steps(t_cub3D*cb, int n)
{
	if (!n)
	{
		while (cb->var.hy < cb->var.m_height && cb->var.hy > 0)
		{
			if (cb->var.hx > cb->var.m_width || cb->var.hx < 0)
				break ;
			else if (!is_wall_pixel(cb, cb->var.hx,
					cb->var.hy - (1 * (cb->var.angle > M_PI))))
				break ;
			cb->var.hx += cb->var.hxblock;
			cb->var.hy += cb->var.hyblock;
		}
	}
	else
	{
		while (cb->var.vx < cb->var.m_width && cb->var.vx > 0)
		{
			if (cb->var.vy > cb->var.m_height || cb->var.vy < 0)
				break ;
			else if (!is_wall_pixel(cb, cb->var.vx - (1 * l_s(cb)), cb->var.vy))
				break ;
			cb->var.vx += cb->var.vxblock;
			cb->var.vy += cb->var.vyblock;
		}
	}
}

void	main_work(t_cub3D *cb)
{
	if (cb->var.angle > M_PI)
		horizontal_block(cb, -1, 0);
	else if (cb->var.angle < M_PI)
		horizontal_block(cb, 1, T_S);
	if (cb->var.angle == 0 || cb->var.angle == M_PI)
	{
		cb->var.hx = cb->p.x;
		cb->var.hy = cb->p.y;
	}
	add_steps(cb, 0);
	cb->var.atan = -tan(cb->var.angle);
	if (cb->var.angle > (3 * M_PI) / 2 || cb->var.angle < M_PI / 2)
		vertical_block(cb, 1, T_S);
	else if (l_s(cb))
		vertical_block(cb, -1, 0);
	if (cb->var.angle == 0 || cb->var.angle == M_PI)
	{
		cb->var.hx = cb->p.x;
		cb->var.hy = cb->p.y;
	}
	add_steps(cb, 1);
}

void	rays(void *param)
{
	t_cub3D	*cb;
	int		til_s;

	cb = param;
	til_s = (T_S / 16);
	cb->var.i = -1;
	draw_init(cb);
	while (++cb->var.i < WINDOW_WIDTH)
	{
		cb->var.angle = angle_overlap(cb->var.angle);
		cb->var.atan = -1 / tan(cb->var.angle);
		main_work(cb);
		calculate_dis(cb);
		cb->var.dis_w = cos(((AGNGLE_VUE / 2) * M_PI / 180)
				- (cb->var.i * cb->var.angle_step)) * cb->var.dis_w;
		cb->var.line_lenth = (WINDOW_HEIGHT / 4) / -tan(30)
			* ((double)WINDOW_HEIGHT / cb->var.dis_w);
		cb->var.line_lenth *= 2;
		cb->var.start_wall = WINDOW_HEIGHT / 2 - (cb->var.line_lenth / 2);
		put_tx(cb);
		cb->var.angle += cb->var.angle_step;
	}
}
