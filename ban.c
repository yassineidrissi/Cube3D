/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ban.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:17:13 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/12 19:4 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

float angle_overlap(float angle)
{
	if (angle < 0)
		angle+=2*M_PI;
	else if (angle > 2*M_PI)
		angle-=2*M_PI;
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
	int i = 0;
	int j = 0;
	unsigned int *rgbas;
	rgbas = (unsigned int *)malloc(sizeof(unsigned int) * (height * width));
	while(i < height * width * 4)
	{
		rgbas[j++] = get_rgba(pixels[i], pixels[i+1], pixels[i+2], pixels[i+3]);
		i+=4;
	}
	return(rgbas);
}

unsigned int **map_to_doublemap(t_cub3D *cb, mlx_texture_t *txt)
{
	int height = txt->height;
	int width = txt->width;
	// printf("im here\n");
	unsigned int *map = get_rgbas(txt->pixels, height, width);
	int i = -1;
	int j = -1;
	unsigned int **double_map;
	double_map = malloc(sizeof(int *) *height);
	while (++i < height)
	{
		double_map[i] = malloc(sizeof(int) * width);
		while (++j < width)
			double_map[i][j] = map[i*width + j];
		j = -1;
	}
	free(map);
	return (double_map);
}

void load_textur(t_cub3D *cb)
{
	int i = -1;
	while(++i < 4)
		cb->text[i].img = (unsigned int **)map_to_doublemap(cb, cb->text[i].txtr);
	i = -1;
	while(++i < 4)
	{
		cb->text[i].width = cb->text[i].txtr->width;
		cb->text[i].height = cb->text[i].txtr->height;
	}
	// printf(" the height is %d, and the width %d\n",, cb->text[0].width);		
		// cb->text[0].img[i] = cb->text[0].img[i] << 8 | cb->text[0].img[i] >> 24;
}

// int put_pixel_textur(t_cub3D *cb, )

int load_color(char r, char g, char b, char a)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

unsigned wall_side(t_cub3D *cb,int txt , float angle, int side, int y_wall, float *j)
{
	int i = *j;
	if(!side)
	{
		if (angle > M_PI)
		{
			txt = (int)cb->text[0].width*txt/COF_PIXEL;
			*j += (float)cb->text[0].height/y_wall;
			return(cb->text[0].img[txt][i]);//*(cb->text[0])).width/COF_PIXEL)]);//color is black
		}
			// return(0x00000000);//color is green
			// return (cb->texture[EA].img[(int)cb->texture[EA].width * (int)(angle * (cb->texture[EA].height / (2 * M_PI)))]);
		else
		{
			txt = (int)cb->text[1].width*txt/COF_PIXEL;
			*j += (float) cb->text[1].height/y_wall;
			return(cb->text[1].img[txt][i]);//*cb->text[1].width]);//color is red
		}
			// return(0x0000FFFF);//color is green
			// return (cb->texture[WE].img[(int)cb->texture[WE].width * (int)(angle * (cb->texture[WE].height / (2 * M_PI)))]);
	}
	else
	{
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
		{
			txt = cb->text[2].height*txt/COF_PIXEL;
			*j += (float)cb->text[2].height/y_wall;
			return(cb->text[2].img[txt][i]);//*cb->text[2].width]);
		}
			// return(0xcc0000FF);//color is blue
			// return (cb->texture[SO].img[(int)cb->texture[SO].width * (int)(angle * (cb->texture[SO].height / (2 * M_PI)))]);
		else
		{
			txt = cb->text[3].height*txt/COF_PIXEL;
			*j += (float)cb->text[3].height/y_wall;
			return(cb->text[3].img[txt][i]);
		}
			// return(0xc0ccccFF);//color is yellow
			// return (cb->texture[NO].img[(int)cb->texture[NO].width * (int)(angle * (cb->texture[NO].height / (2 * M_PI)))]);
	}
}

void put_texture(t_cub3D *cb, int Projection_to_wall,int i, float ra , int hv, int y_wall, float txt)
{
	float j = 0;

	while (y_wall > WINDOW_HEIGHT/2 - 3*(Projection_to_wall/2))
	{
		if (y_wall + Projection_to_wall >= 0 && y_wall + Projection_to_wall < WINDOW_HEIGHT)
			mlx_put_pixel(cb->img, i, y_wall + Projection_to_wall , wall_side(cb,((int)(txt)%(COF_PIXEL)) ,ra, hv, Projection_to_wall, &j));
			y_wall--;
			// j++;
		}
}

void draw_3d_image(t_cub3D *cb)
{
	mlx_texture_t *txt = mlx_load_png("./imgs/1337.png");
	unsigned int **img = map_to_doublemap(cb, txt);
	int i = -1;
	int j= -1;
	int width = txt->width;
	int height = txt->height;
	// printf("the width is %d and the height is %d\n",width,height);
	while(++i < height)
	{
		while(++j < width)
		{
			mlx_put_pixel(cb->img2, j + 1000 , i, img[i][j]);
		}
		j = -1;
	}
}
void	test(void *param)
{
	t_cub3D  *cb = param;
	float hx;
	float hy;
	float vx;
	float vy;
	float ra;
	int hv;
	float txt;
	float hyblock;
	float hxblock;
	float vxblock;
	float vyblock;
	float angle_step;
	float atan;
	int x = cb->player.x;
	int y = cb->player.y;
	int i = -1;
	float rx,ry;
	float dis_w ;
	int m_width = cb->map.width*COF_PIXEL;
	int m_height = cb->map.height*COF_PIXEL;
	// printf("the width is %d and the height is %d\n",m_width,m_height);
	load_textur(cb);
	draw_C_F(cb);
	draw_map(cb);
	draw_player(cb, COF_PIXEL/16, ra);
	draw_3d_image(cb);
	ra = cb->angle - (AGNGLE_VUE / 2 * (M_PI / 180));
	angle_step = (AGNGLE_VUE * (M_PI / 180) / WINDOW_WIDTH);
	while (++i < WINDOW_WIDTH)
	{
		ra = angle_overlap(ra);
		atan = -1 / tan(ra);
		if (ra > M_PI)
		{
			hy = ((y / COF_PIXEL) * COF_PIXEL) - 0.001;
			hx = x + (y - hy) * atan;
			hyblock = -COF_PIXEL;
			hxblock = -hyblock * atan;
		}
		else if (ra < M_PI)
		{
			hy = ((y / COF_PIXEL) * COF_PIXEL) + COF_PIXEL;
			hx = x + (y - hy) * atan;
			hyblock = COF_PIXEL;
			hxblock = -hyblock * atan;
		}
		if (ra == 0 || ra == M_PI)
		{
			hx = x;
			hy = y;
		}
		while (hy < m_height && hy > 0 )// WINDOW_HEIGHT && hy > 0)
		{
			if (hx > m_width || hx < 0)//WINDOW_WIDTH + 1000 || hx < 0)
				break ;
			else if (!is_wall_pixel(cb, hx, hy))
				break ;
			hx += hxblock;
			hy += hyblock;
		}
		
		atan = -tan(ra);
		if (ra > (3 * M_PI) / 2 || ra < M_PI / 2)
		{
			vx = ((x / COF_PIXEL) * COF_PIXEL) + COF_PIXEL;
			vy = y + (x - vx) * atan;
			vxblock = COF_PIXEL;
			vyblock = -vxblock * atan;
		}
		else if (ra < (3 * M_PI) / 2 && ra > M_PI / 2)
		{
			vx = ((x / COF_PIXEL) * COF_PIXEL) - 0.001;
			vy = y + (x - vx) * atan;
			vxblock = -COF_PIXEL;
			vyblock = -vxblock * atan;
		}
		if (ra == 0 || ra == M_PI)
		{
			hx = x;
			hy = y;
		}

		while (vx < m_width && vx > 0 && is_wall_pixel(cb, vx, vy)) // WINDOW_WIDTH + 1000 && vx > 0)
		{
			// printf("x[%d] y[%d]  c[%c]\n", (int)hx / COF_PIXEL, (int)hy / COF_PIXEL, cb->map.map_tmp[(int)hy / COF_PIXEL][(int)hx / COF_PIXEL]);
			if (vy > m_height || vy < 0)// WINDOW_HEIGHT || vy < 0)
				break ;
			else if (!is_wall_pixel(cb, vx, vy))
				break ;
			vx += vxblock;
			vy += vyblock;
		}
		
		float dis_h = sqrt((hx - x) * (hx - x) + (hy - y) * (hy - y));
		float dis_v = sqrt((vx - x) * (vx - x) + (vy - y) * (vy - y));
		if (dis_h < dis_v)
		{
			dis_w = dis_h;
			rx = hx;
			ry = hy;
			hv = 0;// is this horizontal or vertical intersection 
			txt = rx;

		}
		else
		{
			dis_w = dis_v;
			rx = vx;
			ry = vy;
			hv = 1;
			txt = ry;
		}
		
		// printf("hx[%f] hy[%f]\n",hx,hy);
		//printf("x[%f] y[%f]  vx[%f] vy[%f]\n", x, y, vx, vy);
		dis_w = cos(((AGNGLE_VUE / 2) *M_PI/180) - (i * angle_step)) * dis_w;
		float Projection_to_wall = ((float)WINDOW_HEIGHT/4)/-tan(30) * ((float)WINDOW_HEIGHT/dis_w);
		Projection_to_wall *= 2; //wall is square 
		// if (Projection_to_wall > WINDOW_HEIGHT)
		// 	Projection_to_wall = WINDOW_HEIGHT;
		draw_line(cb->img2, x/4, y/4, rx/4, ry/4, 0x000000FF);//line draw
		int y_wall = WINDOW_HEIGHT/2-(Projection_to_wall/2);
		int j = 0;
		// draw_line(cb->img, i, y_wall, i, y_wall + Projection_to_wall,wall_side(cb,((int)(txt)/(COF_PIXEL)) ,ra, hv, Projection_to_wall, &j));//line draw
		put_texture(cb, Projection_to_wall,i, ra , hv ,  y_wall , txt);
		ra += angle_step;
	}
}