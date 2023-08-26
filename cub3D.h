/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 06:47:35 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/26 16:23:40 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include  "MLX42/include/MLX42/MLX42.h"
// # include "validation/validation.h"
# include "./srcs/get_next_line.h"
# include "./srcs/srcs.h"

# define MAP_MAX_ROWS 2880
# define MAP_MAX_COLS 5120
# define BUFFER_SIZE 1000
# define TILE_SIZE 64
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define FOV 60 * (M_PI / 180)
# define SPEED 10
# define COF_PIXEL 50//After validation 2D map , we need to change it to 1
# define AGNGLE_VUE 45
# define ROT_SPEED 0.1
# define ESC 65307
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 0
# define C 1
# define W 119
# define S 115
# define A 97
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265358979323846
# define TWO_PI 6.28318530718
# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20
# define MINIMAP_SCALE_FACTOR 0.3
# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
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
	char	*path;
	int		bol;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_texture;
typedef struct s_player
{
	float		x;
	float		y;
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
	t_map  		map;
	t_player 	player;
	t_texture   text[4];
	t_colore	colors[2];
	int			p;
	int		angle;
	int   	 	fd;
	int			fdr;
	char		**cnt;
	char		*line;
	char		*joined_map;
	char		*s2[4];
	int			map_bol;
	int			nl;
}       t_cub3D;

/*################################################################*/
/*                       validation functions         			  */
/*################################################################*/

void	init_cub3D(t_cub3D *cb);
void	ft_to_space(char *str);
int		compare(t_cub3D *cb);
int		check_parameters(char *av);
int		check_content(t_cub3D *cb);
int		fill_type(t_cub3D *cb);
void	remove_nl(char *str);

/*################################################################*/
/*                       config functions         			  */
/*################################################################*/

void	ft_hook(void* param);
void	draw_C_F(t_cub3D *cb);
void	draw_map(t_cub3D *cb);
void	draw_player(t_cub3D *cb, int angle, int playerSize, int angle_vue);
int		is_wall_pixel(t_cub3D *cb, float x, float y);

#endif