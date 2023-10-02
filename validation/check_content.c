/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:56:45 by yaidriss          #+#    #+#             */
/*   Updated: 2023/10/02 10:38:51 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	edge(t_cub3D *cb, int x, int y)
{
	if (y < 0 || y >= cb->map.height || x < 0)
		return (handl_errors(1), 0);
	return (1);
}

void	check_all_sides(char **str, int x, int y)
{
	if (str[y][x] != '1' && str[y][x] != '0'
		&& str[y][x] != 'N' && str[y][x] != 'S'
		&& str[y][x] != 'W' && str[y][x] != 'E')
	{
		ft_free_double(str);
		handl_errors(10);
	}
}

void	check_valid_map(t_cub3D *cb)
{
	int	x;
	int	y;

	y = -1;
	cb->map.width = 0;
	while (cb->map.map_tmp[++y])
	{
		x = 0;
		while (cb->map.map_tmp[y][x])
		{
			if (p_or_z(cb, cb->map.map_tmp[y][x], x, y) && edge(cb, x - 1, y))
				check_all_sides(cb->map.map_tmp, x - 1, y);
			if (p_or_z(cb, cb->map.map_tmp[y][x], x, y) && edge(cb, x + 1, y))
				check_all_sides(cb->map.map_tmp, x + 1, y);
			if (p_or_z(cb, cb->map.map_tmp[y][x], x, y) && edge(cb, x, y - 1))
				check_all_sides(cb->map.map_tmp, x, y - 1);
			if (p_or_z(cb, cb->map.map_tmp[y][x], x, y) && edge(cb, x, y + 1))
				check_all_sides(cb->map.map_tmp, x, y + 1);
			x++;
		}
		cb->map.width = ft_max(cb->map.width, x);
	}
}

void	load_text(t_cub3D *cb)
{
	mlx_image_t	*logo;
	int			i;

	i = -1;
	while (++i < 4)
	{
		cb->text[i].txtr = mlx_load_png(cb->text[i].path);
		if (!cb->text[i].txtr)
			handl_errors(1);
	}
	cb->logo[0].txtr = mlx_load_png("imgs/1337.png");// we dont need that
	cb->logo->img = map_to_doublemap(cb, cb->logo[0].txtr);
	load_text2(cb);
}

int	check_content(t_cub3D *cb)
{
	cb->line = get_next_line(cb->fd);
	while (cb->line)
	{
		if (fill_type(cb))
		{
			close(cb->fd);
			free(cb->line);
			handl_errors(6);
		}
		free(cb->line);
		cb->line = get_next_line(cb->fd);
	}
	close(cb->fd);
	load_text(cb);
	check_bol(cb);
	check_repeat(cb);
	cb->map.map_tmp = ft_split(cb->joined_map, '\n');
	free(cb->joined_map);
	check_valid_map(cb);
	return (0);
}
