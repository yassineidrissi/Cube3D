/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 06:47:35 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/26 15:41:22 by zouaraqa         ###   ########.fr       */
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
// # include "validation/validation.h"
# include "./srcs/get_next_line.h"
# include "./srcs/srcs.h"

# define MAP_MAX_ROWS 2880
# define MAP_MAX_COLS 5120
# define BUFFER_SIZE 1000
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define RAISE_COLOR 0xFF5733FF
# define SPEED 10
# define TILE_SIZE 64//After validation 2D map , we need to change it to 1
# define MAP_SIZE (TILE_SIZE/16)
# define MAP_COFF 4
# define AGNGLE_VUE 60 
# define ANGLE_MOV 0.087266
# define ROT_SPEED 0.1
# define ESC 65307
# define N 0
# define S 1
# define WE 2
# define EA 3
# define F 0
# define C 1
# define W 119
# define A 97
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265358979323846
# define TWO_PI 6.28318530718
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20
# define MINIMAP_SCALE_FACTOR 0.3
# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1000
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define NUM_TEXTURES 5
# define FPS 30
# define NUM_RAYS WINDOW_WIDTH
# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV / 2))
# define PROJECTED_SLICE_HEIGHT (TILE_SIZE / ray.dist * DIST_PROJ_PLANE)
# define NUM_SPRITES 19
# define SPRITE_WIDTH 64
# define SPRITE_HEIGHT 64
# define NUM_TEXTURES 5
# define NUM_MAPS 3

typedef struct s_map
{
	char	**map_tmp;
	char	map[2800][2900];//[MAP_MAX_ROWS][MAP_MAX_COLS];
	int		width;
	int		height;
}				t_map;
typedef struct s_texture
{
	mlx_texture_t* txtr;
	char	*path;
	int		bol;
	unsigned int 	**img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_texture;
typedef struct s_player
{
	int		x;
	int		y;
	double	width;
	double	height;
	int		turn_direction;
	int		walk_direction;
	double	rotation_angle;
	double	walk_speed;
	double	turn_speed;
}				t_player;   
typedef struct s_colore
{
	int		r;
	int		g;
	int		b;
	int 	bol;
}				 t_colore;

//!add img and mlx variables in t_cub3D struct
typedef struct s_cub3D
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img2;
	mlx_image_t	*img3;
	t_map  		map;
	t_player 	player;
	t_texture   text[4];
	t_colore	colors[2];
	int			p;
	float		angle;
	int   	 	fd;
	char		**cnt;
	int			fdr;
	t_texture	logo[3];
	char		*line;
	char		*joined_map;
	char		*EWSN[4];
	int			map_bol;
	int			nl;
	float	ray_dis;
}       t_cub3D;

typedef struct s_putxt
{
	int line_lenth;
	int i;
	double angle;
	int hv;
	int start_wall;
	double tx;
}t_putxt;

typedef struct s_pos
{
    int      x;
    int      y;
	int		 w; 
}                t_pos;

/*################################################################*/
/*                       validation functions         			  */
/*################################################################*/

void	init_cub3d(t_cub3D *cb);
void	ft_to_space(char *str);
void	remove_nl(char *str);
void	check_bol(t_cub3D *cb);
void	check_repeat(t_cub3D *cb);
void	ft_count_quote(char *str);
int		compare(t_cub3D *cb);
int		check_parameters(char *av);
int		check_content(t_cub3D *cb);
int		fill_type(t_cub3D *cb);
int		p_or_z(t_cub3D *cb, char c, int x, int y);
int 	ft_max(int a, int b);
int		ft_max(int a, int b);

/*################################################################*/
/*                       config functions         			  */
/*################################################################*/

void	ft_hook(void* param);
void	draw_C_F(t_cub3D *cb);
void	draw_map(t_cub3D *cb);
void	draw_player(t_cub3D *cb, int playerSize, int angle_vue);
void	mlx_draw_line(t_cub3D *cb, int x1, int y1, int x2, int y2, uint32_t color);
void	draw_line(mlx_image_t *img, int start_x, int start_y, int end_x, int end_y, size_t color);
// t_pos   ft_calculate_next_wall(t_cub3D *cb, float angle);
// float	dis(t_cub3D *cb,t_pos a);
int		is_wall_pixel(t_cub3D *cb, double x, double y);

/*################################################################*/
/*                      texture 								 */
/*################################################################*/

double angle_overlap(double angle);
unsigned int get_rgba(int r, int g, int b, int a);
unsigned int *get_rgbas(uint8_t *pixels, int height, int width);
unsigned int **map_to_doublemap(t_cub3D *cb, mlx_texture_t *txtr);
void load_text2(t_cub3D *cb);
int load_color(char r, char g,char b, char a);
unsigned pixel_value(t_cub3D *cb, double tx, double angle, int hv, int start_wall, int ty);
int height_image(t_cub3D *cb, int hv, double angle);
void put_textur(t_cub3D *cb, int line_lenth, int i, double angle, int hv, int start_wall, double tx);
void double_free_int(unsigned int **map, int height, int width);
void draw_3d_image(t_cub3D *cb);
void test(void *param);


void	test(void *param);

#endif