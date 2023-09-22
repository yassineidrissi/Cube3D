/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:56:52 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/22 15:13:38 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_cub3D(t_cub3D *cb)
{
	cb->joined_map = NULL;
	cb->line = NULL;
	cb->map_bol = 0;
	cb->text[NO].bol = 0;
	cb->text[SO].bol = 0;
	cb->text[WE].bol = 0;
	cb->text[EA].bol = 0;
	cb->colors[F].bol = 0;
	cb->colors[C].bol = 0;
	cb->p = 0;
	cb->nl = 0;
	cb->map.height = 0;
	cb->EWSN[0] = "NO";
	cb->EWSN[1] = "SO";
	cb->EWSN[2] = "WE";
	cb->EWSN[3] = "EA";
}

void	ft_to_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ',' || str[i] == '\t' || str[i] == '\n')
			str[i] = ' ';
}

void	remove_nl(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			str[i] = '\0';
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
		while (cb->cnt[0][j] && cb->cnt[0][j] == cb->EWSN[i][k])
		{
			j++;
			k++;
		}
		if (!cb->cnt[0][j] && !cb->EWSN[i][k])
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
