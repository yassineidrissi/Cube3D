/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:45:02 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/08/21 13:23:41 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

// void fill_texture_img(t_cube3d *cb)
// {
// 	int i;

// 	i = -1;
// 	while (cb->text[++i].path)
// 	{
// 		cb->text[i].img = mlx_xpm_file_to_image(cb->mlx, cb->text[i].path, &cb->text[i].width, &cb->text[i].height);
// 		if (!cb->text[i].img)
// 			handl_errors(6);
// 		cb->text[i].addr = mlx_get_data_addr(cb->text[i].img, &cb->text[i].bits_per_pixel, &cb->text[i].line_length, &cb->text[i].endian);
// 	}
// }

void	fill_texture(t_cube3d *cb)
{
	int	i;

	i = 0;
	ft_to_space(cb->line);
	cb->cnt = ft_split(cb->line, ' ');

	if (!cb->cnt)
		handl_errors(6);
	while (cb->cnt[i])
		i++;
	if (i != 2 || compare(cb))
	{
		ft_free_double(cb->cnt);
		handl_errors(10);
	}
	/*it says leaks cb->cnt but we neet to work with */
	//ft_free_double(cb->cnt);
	//free it to test leeks in other places
	
	//########## load png in another fun 
	// mlx_texture_t* texture = mlx_load_png(cb->text->cnt[1]);
	// if (!texture)
    //     handl_errors(6);
}

void ft_fill_color(t_cube3d *cb, char **RGB, int i)
{
	int j;

	j = 0;
	while (RGB[j])
		j++;
	if (j != 4) // to prevent seg if there is no r g b in map
	{
		ft_free_double(RGB);
		handl_errors(10);
	}
	// printf("*********************\n");
	// printf("RGB[1] = %s\n", RGB[1]);
	// printf("RGB[2] = %s\n", RGB[2]);
	// printf("RGB[3] = %s\n", RGB[3]);
	cb->colors[i].r = ft_atoi(RGB[1]);
	cb->colors[i].g = ft_atoi(RGB[2]);
	cb->colors[i].b = ft_atoi(RGB[3]);
	cb->colors[i].bol++;
	cb->map_bol++;
	if (cb->colors[i].r < 0 || cb->colors[i].g < 0
		|| cb->colors[i].b < 0 || cb->colors[i].r > 255
		|| cb->colors[i].g > 255 || cb->colors[i].b > 255)
	{
		ft_free_double(RGB);
		handl_errors(10);
	}
	// printf("r = %d, g = %d, b = %d\n",cb->colors[i].r, cb->colors[i].g, cb->colors[i].b);
}

void	fill_colors(t_cube3d *cb)
{
	char **RGB;
	int i;
	int j;

	i = 0;
	j = 0;
	ft_to_space(cb->line);
	RGB = ft_split(cb->line, ' ');
	// printf("color %s\n", cb->line);
	// printf("LRGB[%d] = %s\n", i, RGB[i]);
	if (RGB[0][0] == 'F' && !RGB[0][1] && i < 4)
		ft_fill_color(cb, RGB, F);
	else if (RGB[0][0] == 'C' && !RGB[0][1] && i < 4)
		ft_fill_color(cb, RGB, C);
	else
	{
		ft_free_double(RGB);
		handl_errors(1);
	}
	ft_free_double(RGB);
}
void	fill_map(t_cube3d *cb)
{
	int	i;

	i = 0;
	if (cb->map_bol != 6)
		handl_errors(5);
	// while (cb->line[i])
		
	// return ;
	// printf("map %s\n", cb->line);
}

int fill_type(t_cube3d *cb)
{
	int i;

	i = 0;
	while (cb->line[i] == ' ' || cb->line[i] == '\t')
		i++;
	if (cb->line[i] == 'N' || cb->line[i] == 'S'
		|| cb->line[i] == 'W' || cb->line[i] == 'E')
		fill_texture(cb);
	else if (cb->line[i] == 'F' || cb->line[i] =='C')
		fill_colors(cb);
	else if (cb->line[i] != '\n')
		fill_map(cb);
	// else if (cb->line[i] != '\n')
		// handl_errors(10);
	return (0);
}
