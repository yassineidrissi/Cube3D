/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:57:01 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/20 15:54:53 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
/*
int	compare(char *s1)
{
	char	*s2[4];
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	s2[0] = "NO";
	s2[1] = "SO";
	s2[2] = "WE";
	s2[3] = "EA";
	while (s2[i])
	{
		j = 0;
		k = 0;
		while (s1[j] && s1[j] == s2[i][k] && i < 2)
		{
			j++;
			k++;
		}
		if (!s1[j] && !s2[i][k])
			return (0);
		i++;
	}
	return (1);
}

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

void	fill_texture(t_cube3d *cb)
{
	cb->map.map_tmp = ft_split(cb->line, ' ');
	if (compare(cb->map.map_tmp[0]))
		handl_errors(6);
	pause();
	mlx_texture_t* texture = mlx_load_png(cb->map.map_tmp[1]);
	if (!texture)
        handl_errors(6);
	printf("text %s\n", cb->line);
}
void	fill_color(t_cube3d *cb)
{
	printf("color %s\n", cb->line);
}
void	fill_map(t_cube3d *cb)
{
	// return ;
	printf("map %s\n", cb->line);
}

int fill_type(t_cube3d *cb)
{
	int i;

	i = 0;
	while (cb->line[i] == ' ' || cb->line[i] == '\t')
		i++;
	if (cb->line[i] == 'N' || cb->line[i] == 'S' || cb->line[i] == 'W' || cb->line[i] == 'E')
		fill_texture(cb);
	else if (cb->line[i] == 'F' || cb->line[i] =='C')
		fill_color(cb);
	else if (cb->line[i] == '1')
		fill_map(cb);
	else if (cb->line[i] != '\n')
		handl_errors(10);
	return (0);
}
*/
// void init_cube3d(t_cube3d *cb)
// {
// 	return;
// 	// cb.map = init_map(fd);
// }

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

// void	change_neighbor(char **mp, int i, int j)
// {
// 	if (mp[i][j - 1] != 'V' && mp[i][j - 1] != '1')
// 				mp[i][j - 1] = 'V';
// 	if (mp[i][j + 1] != 'V' && mp[i][j + 1] != '1')
// 				mp[i][j + 1] = 'V';
// 	if (mp[i + 1][j] != 'V' && mp[i + 1][j] != '1')
// 				mp[i + 1][j] = 'V';
// 	if (mp[i - 1][j] != 'V' && mp[i - 1][j] != '1')
// 				mp[i - 1][j] = 'V';
// }
