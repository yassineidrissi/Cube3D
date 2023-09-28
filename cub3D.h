/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 06:47:35 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/28 15:38:23 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <MLX42/MLX42.h>
# include "./srcs/get_next_line.h"
# include "./srcs/srcs.h"

# define BUFFER_SIZE 1000
# define RAISE_COLOR 0xFF5733FF
# define SPEED 10
# define TILE_SIZE 64//After validation 2D map , we need to change it to 1
# define AGNGLE_VUE 60 
# define ANGLE_MOV 0.087266
# define N 0
# define S 1
# define WE 2
# define EA 3
# define F 0
# define C 1
# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1000

typedef struct s_map
{
	char	**map_tmp;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	mlx_texture_t	*txtr;
	unsigned int	**img;
	char			*path;
	char			*addr;
	int				bol;
	int				width;
	int				height;
}	t_texture;

typedef struct s_player
{
	int		x;
	int		y;
	double	width;
	double	height;
}	t_player;

typedef struct s_colore
{
	int	r;
	int	g;
	int	b;
	int	bol;
}	t_colore;

typedef struct s_var
{
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	tx;
	double	angle;
	double	hyblock;
	double	hxblock;
	double	vxblock;
	double	vyblock;
	double	angle_step;
	double	line_lenth;
	double	dis_w;
	double	atan;
	double	rx;
	double	ry;
	int		i;
	int		hv;
	int		x;
	int		y;
	int		m_width;
	int		m_height;
	int		start_wall;
}	t_var;

typedef struct s_cub3D
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img2;
	mlx_image_t	*img3;
	t_texture	text[4];
	t_texture	logo[3];
	t_colore	colors[2];
	t_player	p;
	t_map		map;
	t_var		var;
	char		**cnt;
	char		*line;
	char		*joined_map;
	char		*ewsn[4];
	float		angle;
	int			map_bol;
	int			player;
	int			fd;
	int			nl;
}	t_cub3D;

typedef struct s_putxt
{
	double	angle;
	double	tx;
	int		line_lenth;
	int		start_wall;
	int		hv;
	int		i;
}	t_putxt;

typedef struct s_pos
{
	int	x;
	int	y;
	int	w; 
}	t_pos;

/*################################################################*/
/*                       validation functions         			  */
/*################################################################*/
void			init_cub3d(t_cub3D *cb);
void			ft_to_space(char *str);
void			remove_nl(char *str);
void			check_bol(t_cub3D *cb);
void			check_repeat(t_cub3D *cb);
void			ft_count_quote(char *str);
int				compare(t_cub3D *cb);
int				check_parameters(char *av);
int				check_content(t_cub3D *cb);
int				fill_type(t_cub3D *cb);
int				p_or_z(t_cub3D *cb, char c, int x, int y);
int				ft_max(int a, int b);
int				ft_max(int a, int b);

/*################################################################*/
/*                       config functions         			      */
/*################################################################*/
void			ft_hook(void *param);
void			draw_C_F(t_cub3D *cb);
void			draw_map(t_cub3D *cb);
void			draw_player(t_cub3D *cb, int playerSize);
void			mlx_draw_line(t_cub3D *cb, int x1, int y1, int x2, int y2, uint32_t color);
void			draw_line(mlx_image_t *img, int start_x, int start_y, int end_x, int end_y, size_t color);
int				is_wall_pixel(t_cub3D *cb, double x, double y);

/*################################################################*/
/*                      texture 								  */
/*################################################################*/
int				height_image(t_cub3D *cb, int hv, double angle);
double			angle_overlap(double angle);
void			load_text2(t_cub3D *cb);
void			double_free_int(unsigned int **map, int height, int width);
void			draw_3d_image(t_cub3D *cb);
void			put_texture(t_cub3D *cb, t_putxt *p);
void			put_tx(t_cub3D *cb);
unsigned int	get_rgba(int r, int g, int b, int a);
unsigned int	*get_rgbas(uint8_t *pixels, int height, int width);
unsigned int	**map_to_doublemap(t_cub3D *cb, mlx_texture_t *txtr);
unsigned		pixel_value(t_cub3D *cb, double tx, double angle,
		int hv, int start_wall, int ty);

int				l_s(t_cub3D *cb);
void			draw_init(t_cub3D *cb);
void			calculate_dis(t_cub3D *cb);
void			test(void *param);

#endif