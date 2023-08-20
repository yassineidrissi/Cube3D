/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 06:47:35 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/20 12:01:46 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <MLX42/MLX42.h>
# include "./validation/validation.h"
# include "./srcs/get_next_line.h"
# include "./srcs/srcs.h"

# define MAP_MAX_ROWS 2880
# define MAP_MAX_COLS 5120
# define BUFFER_SIZE 1000
# define TILE_SIZE 64
# define FOV 60 * (M_PI / 180)
# define SPEED 10
# define ROT_SPEED 0.1
# define ESC 65307
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define W 119
# define W 119
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
    int		map_width;
    int		map_height;
}				t_map;
typedef struct s_texture
{
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
    double	x;
    double	y;
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
}				t_colore;

typedef struct s_cube3d
{
    void	*mlx;
    t_map  map;
    t_player player;
    t_texture text[4];
    t_colore floor;
    int fd;
    int fdr;
    
}       t_cube3d;
    // void	*img;
    // char	*addr;
    // int		bits_per_pixel;
    // int		line_length;
    // int		endian;

#endif