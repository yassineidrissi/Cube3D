/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtur_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:46:06 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/10/06 08:58:31 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	unsigned int	c;

	c = (r << 24 | g << 16 | b << 8 | a);
	return (c);
}

unsigned int	*get_rgbas(uint8_t *pixels, int height, int width)
{
	unsigned int	*rgbas;
	int				i;
	int				j;

	i = 0;
	j = 0;
	rgbas = (unsigned int *)malloc(sizeof(unsigned int) * (height * width));
	while (i < height * width * 4)
	{
		rgbas[j++] = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i
				+ 3]);
		i += 4;
	}
	return (rgbas);
}

unsigned int	**map_to_doublemap(t_cub3D *cb, mlx_texture_t *txtr)
{
	unsigned int	*map;
	unsigned int	**double_map;

	map = get_rgbas(txtr->pixels, txtr->height, txtr->width);
	cb->i = -1;
	cb->j = -1;
	cb->y = -1;
	double_map = malloc(sizeof(int *) * txtr->height);
	while (++cb->i < txtr->height)
		double_map[cb->i] = malloc(sizeof(int) * txtr->width);
	cb->i = -1;
	while (++cb->i < txtr->height)
	{
		while (++cb->j < txtr->width)
			double_map[cb->i][cb->j] = map[++cb->y];
		cb->j = -1;
	}
	free(map);
	return (double_map);
}

void	load_text2(t_cub3D *cb)
{
	int	i;

	i = -1;
	cb->pos_logo = 0;
	cb->t = 0;
	while (++i < 4)
		if (cb->text[i].txtr)
			cb->text[i].img = (unsigned int **)map_to_doublemap(cb,
					cb->text[i].txtr);
	i = -1;
	while (++i < 4)
	{
		cb->text[i].width = cb->text[i].txtr->width;
		cb->text[i].height = cb->text[i].txtr->height;
	}
}
