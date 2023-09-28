/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ban.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:54:00 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/28 11:41:34 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

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
			i = (double)cb->text[N].width*(tx)/TILE_SIZE;
			// tx = (int)cb->text[0].width - tx;
			// ty += (int)cb->text[N].height/start_wall;
			return(cb->text[N].img[ty][i]);//*(cb->text[0])).width/TILE_SIZE)]);//color is black
		}
			// return(0x00000000);//color is green
			// return (cb->texture[EA].img[(int)cb->texture[EA].width * (int)(angle * (cb->texture[EA].height / (2 * M_PI)))]);
		else
		{
			i = (int)cb->text[S].width*(tx)/TILE_SIZE;
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
			i = cb->text[WE].height*tx/TILE_SIZE;
			// tx = (int)cb->text[2].width - tx;
			// ty += (double)cb->text[WE].height/start_wall;
			return(cb->text[WE].img[ty][i]);//*cb->text[2].width]);
		}
			// return(0xcc0000FF);//color is blue
			// return (cb->texture[SO].img[(int)cb->texture[SO].width * (int)(angle * (cb->texture[SO].height / (2 * M_PI)))]);
		else
		{
			i = cb->text[EA].height*tx/TILE_SIZE;
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
		if (p->start_wall  >= 0 && p->start_wall <= WINDOW_HEIGHT)// && ty > 0 && ty < ty_max)
			mlx_put_pixel(cb->img, p->i, p->start_wall , pixel_value(cb,(fmod(p->tx, TILE_SIZE)) ,p->angle, p->hv, p->line_lenth,ty));
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
	// printf("the width is %d and the height is %d\n",width,height);
	// reverse_3d_map(img, width, height);
	while(++i < height)
	{
		while(++j < width)
			mlx_put_pixel(cb->img2, j + 1000 ,i, img[i][j]);
		j = -1;
	}
}

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
	draw_C_F(cb);
	draw_map(cb);
	draw_player(cb, TILE_SIZE / ((TILE_SIZE / 16) * 4));
	draw_3d_image(cb);
	cb->var.m_width = cb->map.width * TILE_SIZE;
	cb->var.m_height = cb->map.height * TILE_SIZE;
	cb->var.angle = cb->angle - (AGNGLE_VUE / 2 * (M_PI / 180));
	cb->var.angle_step = (AGNGLE_VUE * (M_PI / 180) / WINDOW_WIDTH);
}

void	horizontal_block(t_cub3D *cb, int signe, int tile_s)
{
	cb->var.hy = (cb->p.y / TILE_SIZE) * TILE_SIZE + tile_s;
	cb->var.hx = cb->p.x + (cb->p.y - cb->var.hy) * cb->var.atan;
	cb->var.hyblock = TILE_SIZE * signe;
	cb->var.hxblock = -cb->var.hyblock * cb->var.atan;
}

void	vertical_block(t_cub3D *cb, int signe, int tile_s)
{
	cb->var.vx = ((cb->p.x / TILE_SIZE) * TILE_SIZE) + tile_s;
	cb->var.vy = cb->p.y + (cb->p.x - cb->var.vx) * cb->var.atan;
	cb->var.vxblock = TILE_SIZE * signe;
	cb->var.vyblock = -cb->var.vxblock * cb->var.atan;
}

int	l_s(t_cub3D *cb)
{
	return (cb->var.angle < (3 * M_PI) / 2 && cb->var.angle > M_PI / 2);
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
		horizontal_block(cb, 1, TILE_SIZE);
	if (cb->var.angle == 0 || cb->var.angle == M_PI)
	{
		cb->var.hx = cb->p.x;
		cb->var.hy = cb->p.y;
	}
	add_steps(cb, 0);
	cb->var.atan = -tan(cb->var.angle);
	if (cb->var.angle > (3 * M_PI) / 2 || cb->var.angle < M_PI / 2)
		vertical_block(cb, 1, TILE_SIZE);
	else if (l_s(cb))
		vertical_block(cb, -1, 0);
	if (cb->var.angle == 0 || cb->var.angle == M_PI)
	{
		cb->var.hx = cb->p.x;
		cb->var.hy = cb->p.y;
	}
	add_steps(cb, 1);
}

void	test(void *param)
{
	t_cub3D	*cb;
	int		til_s;

	cb = param;
	til_s = (TILE_SIZE / 16);
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
		draw_line(cb->img2, cb->p.x / til_s, cb->p.y / til_s,
			cb->var.rx / til_s, cb->var.ry / til_s, RAISE_COLOR);
		cb->var.start_wall = WINDOW_HEIGHT / 2 - (cb->var.line_lenth / 2);
		put_tx(cb);
		cb->var.angle += cb->var.angle_step;
	}
}
