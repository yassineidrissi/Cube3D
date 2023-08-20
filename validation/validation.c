/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:57:01 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/20 12:48:36 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int check_parameters(char *av)
{
	int i;
	int j;
	char *ext;

	i = 0;
	j = 0;
	ext = ".cub";
	while (av[i])
		i++;
	while (ext[j])
		j++;
	if (i < j)
		return (0);
	while (j >= 0)
	{
		if (av[i] != ext[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

int fill_type(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	
	if ( line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		fill_texture(line);
	else if (line[i] == 'F' || line[i] =='C')
		fill_color(line);
	else if (line[i] == '1')
		fill_map(line);
	else
		handl_errors(10)
	return (0);
}

void init_cube3d(t_cube3d *cb)
{
	
	return;
	// cb.map = init_map(fd);
	
}
// void	fill_map(t_map *map)
// {
// 	char	*buffer;
// 	char	*buffer2;
// 	int		i;

// 	i = -1;
// 	map->next = (char *)1;
// 	buffer = NULL;
// 	while (map->next)
// 	{
// 		map->next = get_next_line(map->fd);
// 		buffer = ft_my_strjoin(buffer, map->next, 1);
// 	}
// 	while (buffer[++i])
// 		if (buffer[0] == '\n' || (buffer[i] == '\n' && buffer[i + 1] == '\n'))
// 			handl_errors(3);
// 	buffer2 = ft_strdup(buffer);
// 	map->map = ft_split(buffer, '\n');
// 	if (!map->map[0])
// 		handl_errors(3);
// 	map->map2 = ft_split(buffer2, '\n');
// 	free(buffer);
// 	free(buffer2);
// }

// void	test_rectangular(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
// 	map->hight = 0;
// 	while (map->map[map->hight])
// 		map->hight++;
// 	map->width = ft_strlen(map->map[0]);
// 	while (map->map[i])
// 		if (ft_strlen(map->map[i++]) == map->width)
// 			j++;
// 	if (j != map->hight)
// 		handl_errors(3);
// }

// void	test_walls(t_map *map)
// {
// 	int	i;

// 	i = -1;
// 	while (map->map[0][++i])
// 		if (map->map[0][i] != '1' || map->map[map->hight - 1][i] != '1')
// 			handl_errors(3);
// 	i = -1;
// 	while (++i < map->hight)
// 		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
// 			handl_errors(3);
// }

// void	test_caraters(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	map->count_p = 0;
// 	map->count_e = 0;
// 	map->count_c = 0;
// 	while (++i < map->hight)
// 	{
// 		j = -1;
// 		while (map->map[i][++j])
// 		{
// 			if (map->map[i][j] == 'P')
// 				map->count_p++;
// 			else if (map->map[i][j] == 'C')
// 				map->count_c++;
// 			else if (map->map[i][j] == 'E')
// 				map->count_e++;
// 			else if (map->map[i][j] != '0' && map->map[i][j] != '1')
// 				handl_errors(1);
// 		}
// 	}
// 	if (map->count_p != 1 || map->count_e != 1 || map->count_c < 1)
// 		handl_errors(9);
// }
//!need to set the postion of all character ( Player and exit)

void	change_neighbor(char **mp, int i, int j)
{
	if (mp[i][j - 1] != 'V' && mp[i][j - 1] != '1')
				mp[i][j - 1] = 'V';
	if (mp[i][j + 1] != 'V' && mp[i][j + 1] != '1')
				mp[i][j + 1] = 'V';
	if (mp[i + 1][j] != 'V' && mp[i + 1][j] != '1')
				mp[i + 1][j] = 'V';
	if (mp[i - 1][j] != 'V' && mp[i - 1][j] != '1')
				mp[i - 1][j] = 'V';
}
