/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:47:50 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/10/04 16:58:53 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	edge(t_cub3D *cb, int x, int y)
{
	if (y < 0 || y >= cb->map.height || x < 0)
		return (handl_errors(1), 0);
	return (1);
}

void	inc(int *j, int *k)
{
	(*j)++;
	(*k)++;
}

int	compare(t_cub3D *cb)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 4)
	{
		j = 0;
		k = 0;
		while (cb->cnt[0][j] && cb->cnt[0][j] == cb->ewsn[i][k])
			inc(&j, &k);
		if (!cb->cnt[0][j] && !cb->ewsn[i][k])
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
