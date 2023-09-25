/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ban.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:54:00 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/25 19:50:53 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

float angle_overlap(float angle)
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

unsigned int **map_to_doublemap(t_cub3D *cb, mlx_texture_t *txtr)
{
	int height = txtr->height;
	int width = txtr->width;
	// printf("im here\n");
	unsigned int *map = get_rgbas(txtr->pixels, height, width);
	int i = -1;
	int j = -1;
	int k = width * height;
	unsigned int **double_map;
	double_map = malloc(sizeof(int *) *height);
	while(++i < height)
		double_map[i] = malloc(sizeof(int) * width);
	i = -1;
	while (++i < height)
	{
		// double_map[i] = malloc(sizeof(int) * width);
		while (++j < width)
			double_map[i][j] = map[k--];
		j = -1;
	}
	free(map);
	return (double_map);
}

unsigned int **map_to_doublemap_3d(t_cub3D *cb, mlx_texture_t *txtr)
{
	int height = txtr->height;
	int width = txtr->width;
	// printf("im here\n");
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
		// double_map[i] = malloc(sizeof(int) * width);
		while (++j < width)
			double_map[i][j] = map[++k];
		j = -1;
	}
	free(map);
	return (double_map);
}

void load_textur(t_cub3D *cb)
{
	int i = -1;
	while(++i < 4)
		cb->text[i].img = (unsigned int **)map_to_doublemap_3d(cb, cb->text[i].txtr);
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

unsigned pixel_value(t_cub3D *cb,int tx , float angle, int side, int start_wall, float *j)
{
	int i = *j;
	if(!side)
	{
		if (angle > M_PI)
		{
			tx = (int)cb->text[N].width*(TILE_SIZE - tx)/TILE_SIZE;
			// tx = (int)cb->text[0].width - tx;
			*j += (float)cb->text[N].height/start_wall;
			return(cb->text[N].img[i][tx]);//*(cb->text[0])).width/TILE_SIZE)]);//color is black
		}
			// return(0x00000000);//color is green
			// return (cb->texture[EA].img[(int)cb->texture[EA].width * (int)(angle * (cb->texture[EA].height / (2 * M_PI)))]);
		else
		{
			tx = (int)cb->text[S].width*(TILE_SIZE- tx)/TILE_SIZE;
			// tx = (int)cb->text[1].width - tx;
			*j += (float) cb->text[S].height/start_wall;
			return(cb->text[S].img[i][tx]);//*cb->text[1].width]);//color is red
		}
			// return(0x0000FFFF);//color is green
			// return (cb->texture[WE].img[(int)cb->texture[WE].width * (int)(angle * (cb->texture[WE].height / (2 * M_PI)))]);
	}
	else
	{
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
		{
			tx = cb->text[WE].height*tx/TILE_SIZE;
			// tx = (int)cb->text[2].width - tx;
			*j += (float)cb->text[WE].height/start_wall;
			return(cb->text[WE].img[i][tx]);//*cb->text[2].width]);
		}
			// return(0xcc0000FF);//color is blue
			// return (cb->texture[SO].img[(int)cb->texture[SO].width * (int)(angle * (cb->texture[SO].height / (2 * M_PI)))]);
		else
		{
			tx = cb->text[EA].height*tx/TILE_SIZE;
			// tx = (int)cb->text[2].width - tx;
			*j += (float)cb->text[EA].height/start_wall;
			return(cb->text[EA].img[i][tx]);
		}
			// return(0xc0ccccFF);//color is yellow
			// return (cb->texture[NO].img[(int)cb->texture[NO].width * (int)(angle * (cb->texture[NO].height / (2 * M_PI)))]);
	}
}

int height_image(t_cub3D *cb ,int hv, float angle)
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

void put_texture(t_cub3D *cb, int line_lenth,int i, float  angle , int hv, int start_wall, float tx)
{
	float j = 0;

	while (start_wall > WINDOW_HEIGHT/2 - 3*(line_lenth/2))
	{
		if (start_wall + line_lenth >= 0 && start_wall + line_lenth < WINDOW_HEIGHT)
			mlx_put_pixel(cb->img, i, start_wall + line_lenth , pixel_value(cb,((int)(tx)%(TILE_SIZE)) , angle, hv, line_lenth, &j));
			start_wall--;
			// j++;
		}
}

void double_free_int(unsigned int **map, int height, int width)
{
	int i = -1;
	while (++i < height)
		free(map[i]);
	free(map);
}

// void reverse_3d_map(unsigned int **img, int width, int height)
// {
// 	// printf("im here\n");
// 	int i = -1;
// 	int j = -1;
// 	unsigned int **double_map;
// 	double_map = malloc(sizeof(int *) *height);
// 	while(++i < height)
// 		double_map[i] = malloc(sizeof(int) * width);
// 	i = -1;
// 	while (++i < height)
// 	{
// 		// double_map[i] = malloc(sizeof(int) * width);
// 		while (++j < width)
// 			double_map[i][j] = img[width - 1 - i][height - 1 - j];
// 		j = -1;
// 	}
			
// 	double_free_int(img, height, width);
// 	img = double_map;
// 	// return (double_map);
// }


void draw_3d_image(t_cub3D *cb)
{
	mlx_texture_t *txt = mlx_load_png("./imgs/1337.png");
	unsigned int **img = map_to_doublemap_3d(cb, txt);
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
void	test(void *param)
{
	t_cub3D  *cb = param;
	float hx;
	float hy;
	float vx;
	float vy;
	float angle;
	int hv;
	float tx;
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
	int m_width = cb->map.width*TILE_SIZE;
	int m_height = cb->map.height*TILE_SIZE;
	// printf("the width is %d and the height is %d\n",m_width,m_height);
	load_textur(cb);
	draw_C_F(cb);
	draw_map(cb);
	draw_player(cb, TILE_SIZE/16,  angle);
	draw_3d_image(cb);
	 angle = cb->angle - (AGNGLE_VUE / 2 * (M_PI / 180));
	angle_step = (AGNGLE_VUE * (M_PI / 180) / WINDOW_WIDTH);
	while (++i < WINDOW_WIDTH)
	{
		 angle = angle_overlap( angle);
		atan = -1 / tan( angle);
		if ( angle > M_PI)
		{
			hy = ((y / TILE_SIZE) * TILE_SIZE) - 0.001;
			hx = x + (y - hy) * atan;
			hyblock = -TILE_SIZE;
			hxblock = -hyblock * atan;
		}
		else if ( angle < M_PI)
		{
			hy = ((y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
			hx = x + (y - hy) * atan;
			hyblock = TILE_SIZE;
			hxblock = -hyblock * atan;
		}
		if ( angle == 0 ||  angle == M_PI)
		{
			hx = x;
			hy = y;
		}
		while (hy < m_height && hy > 0 )
		{
			if (hx > m_width || hx < 0)
				break ;
			else if (!is_wall_pixel(cb, hx, hy))
				break ;
			hx += hxblock;
			hy += hyblock;
		}
		
		atan = -tan( angle);
		if ( angle > (3 * M_PI) / 2 ||  angle < M_PI / 2)
		{
			vx = ((x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
			vy = y + (x - vx) * atan;
			vxblock = TILE_SIZE;
			vyblock = -vxblock * atan;
		}
		else if ( angle < (3 * M_PI) / 2 &&  angle > M_PI / 2)
		{
			vx = ((x / TILE_SIZE) * TILE_SIZE) - 0.001;
			vy = y + (x - vx) * atan;
			vxblock = -TILE_SIZE;
			vyblock = -vxblock * atan;
		}
		if ( angle == 0 ||  angle == M_PI)
		{
			hx = x;
			hy = y;
		}

		while (vx < m_width && vx > 0 && is_wall_pixel(cb, vx, vy))
		{
			// printf("x[%d] y[%d]  c[%c]\n", (int)hx / TILE_SIZE, (int)hy / TILE_SIZE, cb->map.map_tmp[(int)hy / TILE_SIZE][(int)hx / TILE_SIZE]);
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
			tx = rx;

		}
		else
		{
			dis_w = dis_v;
			rx = vx;
			ry = vy;
			hv = 1;
			tx = ry;
		}
		
		// printf("hx[%f] hy[%f]\n",hx,hy);
		//printf("x[%f] y[%f]  vx[%f] vy[%f]\n", x, y, vx, vy);
		dis_w = cos(((AGNGLE_VUE / 2) *M_PI/180) - (i * angle_step)) * dis_w;
		float line_lenth = ((float)WINDOW_HEIGHT/4)/-tan(30) * ((float)WINDOW_HEIGHT/dis_w);
		line_lenth *= 2; //wall is square 
		// if (line_lenth > WINDOW_HEIGHT)
		// 	line_lenth = WINDOW_HEIGHT;
		draw_line(cb->img2, x/4, y/4, rx/4, ry/4, 0x000000FF);//line draw
		int start_wall = WINDOW_HEIGHT/2-(line_lenth/2);
		int j = 0;
		// draw_line(cb->img, i, start_wall, i, start_wall + line_lenth,pixel_value(cb,((int)(txt)/(TILE_SIZE)) ,ra, hv, line_lenth, &j));//line draw
		put_texture(cb, line_lenth,i,  angle , hv ,  start_wall , tx);
		 angle += angle_step;
	}
}