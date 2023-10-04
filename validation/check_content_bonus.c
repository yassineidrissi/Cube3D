/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:56:45 by yaidriss          #+#    #+#             */
/*   Updated: 2023/10/04 15:37:26 by yaidriss         ###   ########.fr       */
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
	cb->fn_logo[0] = "imgs/1.png";
	cb->fn_logo[1] = "imgs/2.png";
	cb->fn_logo[2] = "imgs/3.png";
	cb->fn_logo[3] = "imgs/4.png";
	cb->fn_logo[4] = "imgs/5.png";
	while (++i < 4)
	{
		cb->text[i].txtr = mlx_load_png(cb->text[i].path);
		if (!cb->text[i].txtr)
			handl_errors(6);
	}
	i = -1;
	while(++i < 5)
	{
		cb->logo[i].txtr = mlx_load_png(cb->fn_logo[i]);
		if(cb->logo[i].txtr == NULL)
			handl_errors(6);
		cb->logo[i].img = map_to_doublemap(cb, cb->logo[i].txtr);
	}

	load_text2(cb);
}

void	mini_map_size(t_cub3D *cb)
{
	cb->d = 16;
	if (cb->map.height > 35 || cb->map.width > 35)
		cb->d = 1;
	else if (cb->map.width > 430 || cb->map.height > 230)
	{
		ft_free_double(cb->map.map_tmp);
		handl_errors(10);
	}
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
	mini_map_size(cb);
	return (0);
}
