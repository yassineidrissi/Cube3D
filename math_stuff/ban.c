/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ban.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:54:00 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/10/02 10:50:55 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"

double angle_overlap(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2*M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

unsigned int	get_rgba(int r, int g, int b, int a)
{
	unsigned int	c;

	c = (r << 24 | g << 16 | b << 8 | a);
	return (c);
}

unsigned int *get_rgbas(uint8_t *pixels, int height, int width)
{
	unsigned int	*rgbas;
	int				i;
	int				j;

	i = 0;
	j = 0;
	rgbas = (unsigned int *)malloc(sizeof(unsigned int) * (height * width));
	while(i < height * width * 4)
	{
		rgbas[j++] = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
		i += 4;
	}
	return(rgbas);
}

unsigned int ** map_to_doublemap(t_cub3D *cb, mlx_texture_t *txtr)
{
	int height = txtr->height;
	int width = txtr->width;
	unsigned int *map = get_rgbas(txtr->pixels, height, width);
	int i = -1;
	int j = -1;
	int k = -1;
	unsigned int **double_map;
	double_map = malloc(sizeof(int *) *height);
	while(++i < height)
		double_map[i] = malloc(sizeof(int) * width);
	i = -1;
	while (++i < height)
	{
		while (++j < width)
			double_map[i][j] = map[++k];
		j = -1;
	}
	free(map);
	return (double_map);
}

void load_text2(t_cub3D *cb)
{
	int i = -1;
	while(++i < 4)
		cb->text[i].img = (unsigned int **) map_to_doublemap(cb, cb->text[i].txtr);
	i = -1;
	while(++i < 4)
	{
		cb->text[i].width = cb->text[i].txtr->width;
		cb->text[i].height = cb->text[i].txtr->height;
	}
}


int load_color(char r, char g, char b, char a)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

unsigned pixel_value(t_cub3D *cb,double tx , double angle, int hv, int start_wall, int ty)
{
	int i;
	if(!hv)
	{
		if (angle > M_PI)
		{
			i = (double)cb->text[N].width*(tx)/T_S;
			// tx = (int)cb->text[0].width - tx;
			// ty += (int)cb->text[N].height/start_wall;
			return(cb->text[N].img[ty][i]);//*(cb->text[0])).width/T_S)]);//color is black
		}
			// return(0x00000000);//color is green
			// return (cb->texture[EA].img[(int)cb->texture[EA].width * (int)(angle * (cb->texture[EA].height / (2 * M_PI)))]);
		else
		{
			i = (int)cb->text[S].width*(tx)/T_S;
			// tx = (int)cb->text[1].width - tx;
			// ty += (double) cb->text[S].height/start_wall;
			return(cb->text[S].img[ty][i]);//*cb->text[1].width]);//color is red
		}
			// return(0x0000FFFF);//color is green
			// return (cb->texture[WE].img[(int)cb->texture[WE].width * (int)(angle * (cb->texture[WE].height / (2 * M_PI)))]);
	}
	else
	{
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
		{
			i = cb->text[WE].height*tx/T_S;
			// tx = (int)cb->text[2].width - tx;
			// ty += (double)cb->text[WE].height/start_wall;
			return(cb->text[WE].img[ty][i]);//*cb->text[2].width]);
		}
			// return(0xcc0000FF);//color is blue
			// return (cb->texture[SO].img[(int)cb->texture[SO].width * (int)(angle * (cb->texture[SO].height / (2 * M_PI)))]);
		else
		{
			i = cb->text[EA].height*tx/T_S;
			// tx = (int)cb->text[2].width - tx;
			// ty += (double)cb->text[EA].height/start_wall;
			return(cb->text[EA].img[ty][i]);
		}
			// return(0xc0ccccFF);//color is yellow
			// return (cb->texture[NO].img[(int)cb->texture[NO].width * (int)(angle * (cb->texture[NO].height / (2 * M_PI)))]);
	}
}

int height_image(t_cub3D *cb ,int hv, double angle)
{
	if(!hv)
	{
		if (angle > M_PI)
			return (cb->text[N].height);
		else
			return(cb->text[S].height);
	}
	else
	{
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
			return(cb->text[WE].width);
		else
			return(cb->text[EA].width);
	}
}

void put_texture(t_cub3D *cb,t_putxt *p)
{
	double	 ty_max = (double)height_image(cb, p->hv, p->angle) - 1;
	double ty = 0;
	double 	ty_step = ty_max/p->line_lenth;
	while (p->start_wall  < WINDOW_HEIGHT/2 +(p->line_lenth/2))
	{
		if (p->start_wall  >= 0 && p->start_wall <= WINDOW_HEIGHT)
			mlx_put_pixel(cb->img, p->i, p->start_wall , pixel_value(cb,(fmod(p->tx, T_S)) ,p->angle, p->hv, p->line_lenth,ty));
		p->start_wall++;
		ty += ty_step;
	}
}

void double_free_int(unsigned int **map, int height, int width)
{
	int i = -1;
	while (++i < height)
		free(map[i]);
	free(map);
}

void draw_3d_image(t_cub3D *cb)
{
	mlx_texture_t *txt = cb->logo[0].txtr;
	unsigned int **img = cb->logo[0].img;
	int i = -1;
	int j= -1;
	int width = txt->width;
	int height = txt->height;
	while(++i < height)
	{
		while(++j < width)
			mlx_put_pixel(cb->img2, j + 1000 ,i, img[i][j]);
		j = -1;
	}
}
