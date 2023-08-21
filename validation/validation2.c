/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:56:52 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/21 16:05:20 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	remove_nl(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			str[i] = '\0';
}

void	print(char *str, int x)
{
	if (str)
		printf("[%s]\n", str);
	if (x)
		printf("[%d]\n", x);
}
// void	validation(t_map	*map)
// {
// 	test_rectangular(map);
// 	test_walls(map);
// 	test_caraters(map);
// 	test_valid_map(map);
// 	if (!find_path_map(map->map2))
// 		handl_errors(8);
// 	ft_free_double(map->map2);
// 	map->player = ft_location(map, 'P');
// 	map->exit = ft_location(map, 'E');
// }

// void	validation_args(char *v)
// {
// 	char	**s;

// 	s = ft_split(v, '.');
// 	if (!s || !s[0] || !s[1] || s[2] || ft_cmp(s[1], "ber"))
// 	{
// 		ft_free_double(s);
// 		handl_errors(10);
// 	}
// 	ft_free_double(s);
// }

// t_loc	ft_location(t_map *m, char c)
// {
// 	t_loc	pos;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (++i < m->hight)
// 	{
// 		j = -1;
// 		while (m->map[i][++j])
// 		{
// 			if (m->map[i][j] == c)
// 			{
// 					pos.x = i;
// 					pos.y = j;
// 			}
// 		}
// 	}
// 	return (pos);
// }
