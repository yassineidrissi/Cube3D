/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:45:02 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/10/04 16:57:29 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	fill_texture(t_cub3D *cb)
{
	char	*str;
	int		i;

	i = 0;
	non_printable(cb->line);
	str = ft_strtrim(cb->line, " ");
	cb->cnt = ft_split(str, 31);
	free(str);
	if (!cb->cnt)
		handl_errors(6);
	while (cb->cnt[i])
		i++;
	if (i != 2 || compare(cb))
	{
		ft_free_double(cb->cnt);
		handl_errors(10);
	}
	ft_free_double(cb->cnt);
}

void	ft_fill_color(t_cub3D *cb, char **RGB, int i)
{
	int	j;

	j = 0;
	while (RGB[j])
		j++;
	if (j != 4)
	{
		ft_free_double(RGB);
		handl_errors(10);
	}
	cb->colors[i].r = ft_atoi(RGB[1]);
	cb->colors[i].g = ft_atoi(RGB[2]);
	cb->colors[i].b = ft_atoi(RGB[3]);
	cb->colors[i].bol++;
	cb->map_bol++;
	if (cb->colors[i].r < 0 || cb->colors[i].r > 255
		|| cb->colors[i].b < 0 || cb->colors[i].b > 255
		|| cb->colors[i].g < 0 || cb->colors[i].g > 255)
	{
		ft_free_double(RGB);
		handl_errors(10);
	}
}

void	fill_colors(t_cub3D *cb)
{
	char	**rgb;

	ft_count_quote(cb->line);
	ft_to_space(cb->line);
	rgb = ft_split(cb->line, ' ');
	if (rgb[0][0] == 'F' && !rgb[0][1])
		ft_fill_color(cb, rgb, F);
	else if (rgb[0][0] == 'C' && !rgb[0][1])
		ft_fill_color(cb, rgb, C);
	else
	{
		ft_free_double(rgb);
		handl_errors(1);
	}
	ft_free_double(rgb);
}

void	fill_map(t_cub3D *cb)
{
	int	i;

	i = -1;
	cb->nl = 1;
	if (cb->map_bol != 6)
		handl_errors(5);
	cb->joined_map = ft_strjoin(cb->joined_map, cb->line);
	cb->map.height++;
}

int	fill_type(t_cub3D *cb)
{
	int	i;

	i = 0;
	while (cb->line[i] == ' ' || cb->line[i] == '\t')
		i++;
	if (cb->line[i] == 'N' || cb->line[i] == 'S'
		|| cb->line[i] == 'W' || cb->line[i] == 'E')
		fill_texture(cb);
	else if (cb->line[i] == 'F' || cb->line[i] == 'C')
		fill_colors(cb);
	else if (cb->line[i] != '\n')
		fill_map(cb);
	else if (cb->line[i] == '\n' && cb->nl)
		handl_errors(10);
	return (0);
}
