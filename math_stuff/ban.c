/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ban.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:54:00 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/10/03 15:14:08 by zouaraqa         ###   ########.fr       */
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
			return(cb->text[N].img[ty][i]);
		}
		else
		{
			i = (int)cb->text[S].width*(tx)/T_S;
			return(cb->text[S].img[ty][cb->text[S].width -1 - i]);
		}
	}
	else
	{
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
		{
			i = cb->text[WE].width*tx/T_S;
			return(cb->text[WE].img[ty][cb->text[WE].width -1 - i]);
		}
		else
		{
			i = cb->text[EA].width*tx/T_S;
			return(cb->text[EA].img[ty][i]);
		}
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
			return(cb->text[WE].height);
		else
			return(cb->text[EA].height);
	}
}

void put_texture(t_cub3D *cb,t_putxt *p)
{
	double	 ty_max = (double)height_image(cb, p->hv, p->angle) - 1;
	double ty = 0;
	// printf("im here\n");
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
	mlx_texture_t *txt = cb->logo[M].txtr;
	unsigned int **img = cb->logo[M].img;
	mlx_texture_t *txt_l = cb->logo[L].txtr;
	unsigned int **img_l = cb->logo[L].img;
	mlx_texture_t *txt_r = cb->logo[R].txtr;
	unsigned int **img_r = cb->logo[R].img;
	int i = -1;
	int j= -1;
	int width = txt->width;
	int height = txt->height;
	int width_l = txt_l->width;
	int height_l = txt_l->height;
	int height_r = txt_r->height;
	int width_r = txt_r->width;

	while (++i < height_l)
	{
		while (++j < width_l)
			mlx_put_pixel(cb->img2, 1000 + 10 + j*cos(cb->ang_fly), 25 + i + cb->t, img_l[i][j]);
		j = -1;
	}
	
	i = -1;
	j = -1;
	while(++i < height)
	{
		while(++j < width)
			mlx_put_pixel(cb->img2, j + 1000 + width_l ,i  + 5 + cb->t/2, img[i][j]);
		j = -1;
	}
	i = -1;
	j = -1;
	while(++i < height_r)
	{
		while(++j < width_r)
			mlx_put_pixel(cb->img2, j + 1000 + width_l + width, i + cb->t, img_r[i][j]);
		j= -1;
	}
	cb->ang_fly += 0.5;
	cb->t += 2;
	if(cb->ang_fly > M_PI/2)
		cb->ang_fly = 0;
	if(cb->t > 10)
		cb->t = 0;
}
