/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:57:01 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/21 17:51:40 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_cube3d(t_cube3d *cb)
{
	cb->all_map = NULL;
	cb->line = NULL;
	cb->map_bol = 0;
	cb->text[NO].bol = 0;
	cb->text[SO].bol = 0;
	cb->text[WE].bol = 0;
	cb->text[EA].bol = 0;
	cb->colors[F].bol = 0;
	cb->colors[C].bol = 0;
	cb->s2[0] = "NO";
	cb->s2[1] = "SO";
	cb->s2[2] = "WE";
	cb->s2[3] = "EA";
	cb->p = 0;
}

void	ft_to_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ',' || str[i] == '\t' || str[i] == '\n')
			str[i] = ' ';
}

int	compare(t_cube3d *cb)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 4)
	{
		j = 0;
		k = 0;
		while (cb->cnt[0][j] && cb->cnt[0][j] == cb->s2[i][k])
		{
			j++;
			k++;
		}
		if (!cb->cnt[0][j] && !cb->s2[i][k])
		{
			cb->text[i].bol++;
			cb->map_bol++;
			if (cb->text[i].bol != 1)
				return (1);
			else
				cb->text[i].path = ft_strdup(cb->cnt[1]);
			return (0);
		}
	}
	return (1);
}

int check_parameters(char *av)
{
	char 	*ext;
	int 	i;
	int 	j;

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
/* chek bol to see if there is something other than NO SO WE EA F C before arriving to the map*/
void	check_bol(t_cube3d *cb)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (cb->text[i].bol != 1)
			handl_errors(10);
	i = -1;
	while (++i < 2)
		if (cb->colors[i].bol != 1)
			handl_errors(10);
}

/*check player if its repeated or it doesnt exist*/
void	check_repeat(t_cube3d *cb)
{
	int	i;

	i = -1;
	while (cb->all_map[++i])
	{
		if (cb->all_map[i] == 'N' || cb->all_map[i] == 'S'
			|| cb->all_map[i] == 'W' || cb->all_map[i] == 'E')
			cb->p++;
		else if (cb->all_map[i] != '1' && cb->all_map[i] != '0'
				&& cb->all_map[i] != ' ' && cb->all_map[i] != '\t'
				&& cb->all_map[i] != '\n')
		{
			free(cb->all_map);
			handl_errors(10);
		}
	}
	if (cb->p != 1)
	{
			free(cb->all_map);
			handl_errors(4);
	}
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

void	check_valid_map(t_cube3d *cb)
{
	int	x;
	int	y;

	y = -1;
	while (cb->map.map_tmp[++y])
	{
		x = 0;
		while (cb->map.map_tmp[y][x])
		{
			if (cb->map.map_tmp[y][x] == '0')
				check_all_sides(cb->map.map_tmp, x - 1, y);
			if (cb->map.map_tmp[y][x] == '0')
				check_all_sides(cb->map.map_tmp, x + 1, y);
			if (cb->map.map_tmp[y][x] == '0')
				check_all_sides(cb->map.map_tmp, x, y - 1);
			if (cb->map.map_tmp[y][x] == '0')
				check_all_sides(cb->map.map_tmp, x, y + 1);
			x++;
		}
	}
}

int	check_content(t_cube3d *cb)
{
	cb->line = get_next_line(cb->fd);
	while (cb->line)
	{
		if (fill_type(cb))
		{
			printf("im here check inside if fill_type\n");
			free(cb->line);
			handl_errors(6);
		}
		free(cb->line);
		cb->line = get_next_line(cb->fd);
	}
	// close(cb->fd);
	free(cb->line);
	check_bol(cb);
	check_repeat(cb);
	cb->map.map_tmp = ft_split(cb->all_map, '\n');
	free(cb->all_map);

	// for (int i = 0; cb->map.map_tmp[i] ;i++ )
	// 	print(cb->map.map_tmp[i], 0);

	/* my time has come check the valid map if its working */
	check_valid_map(cb);
	return (0);
}

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
