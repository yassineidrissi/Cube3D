/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:48:11 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/10/06 08:53:45 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int	pixel_value(t_cub3D *cb, double tx, t_putxt *p, int ty)
{
	if (!p->hv)
	{
		if (p->angle > M_PI)
			return (cb->text[N].img[ty][(int)(cb->text[N].width * (tx) / T_S)]);
		else
			return (cb->text[S].img[ty][(int)(cb->text[S].width - 1
				- (cb->text[S].width * (tx) / T_S))]);
	}
	else
	{
		if (p->angle > M_PI / 2 && p->angle < (3 * M_PI) / 2)
			return (cb->text[WE].img[ty][(int)(cb->text[WE].width - 1
				- (cb->text[WE].width * tx / T_S))]);
		else
			return (cb->text[EA].img[ty][(int)(cb->text[EA].width * tx / T_S)]);
	}
}

int	height_image(t_cub3D *cb, int hv, double angle)
{
	if (!hv)
	{
		if (angle > M_PI)
			return (cb->text[N].height);
		else
			return (cb->text[S].height);
	}
	else
	{
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
			return (cb->text[WE].height);
		else
			return (cb->text[EA].height);
	}
}

void	put_texture(t_cub3D *cb, t_putxt *p)
{
	double	ty_max;
	double	ty;
	double	ty_step;

	ty_max = height_image(cb, p->hv, p->angle) - 1;
	ty = 0;
	ty_step = ty_max / p->line_lenth;
	while (p->start_wall < WINDOW_HEIGHT / 2 + (p->line_lenth / 2))
	{
		if (p->start_wall >= 0 && p->start_wall < WINDOW_HEIGHT)
			mlx_put_pixel(cb->img, p->i, p->start_wall, pixel_value(cb,
					(fmod(p->tx, T_S)), p, ty));
		p->start_wall++;
		ty += ty_step;
	}
}

void	double_free_int(unsigned int **map, int height, int width)
{
	int	i;

	i = -1;
	while (++i < height)
		free(map[i]);
	free(map);
}

void	draw_3d_image(t_cub3D *cb)
{
	mlx_texture_t	*txt;
	unsigned int	**img;

	txt = cb->logo[M].txtr;
	img = cb->logo[M].img;
	cb->i = -1;
	cb->j = -1;
	while (++cb->i < txt->height)
	{
		while (++cb->j < txt->width)
			mlx_put_pixel(cb->img2, cb->j + 1150, cb->i,
				cb->logo[cb->pos_logo].img[cb->i][cb->j]);
		cb->j = -1;
	}
	cb->t++;
	if (cb->t == 4)
	{
		cb->t = 0;
		cb->pos_logo++;
	}
	if (cb->pos_logo == 5)
		cb->pos_logo = 0;
}
