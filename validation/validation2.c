/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:56:52 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/27 16:16:11 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_cub3d(t_cub3D *cb)
{
	cb->joined_map = NULL;
	cb->line = NULL;
	cb->map_bol = 0;
	cb->text[N].bol = 0;
	cb->text[S].bol = 0;
	cb->text[WE].bol = 0;
	cb->text[EA].bol = 0;
	cb->colors[F].bol = 0;
	cb->colors[C].bol = 0;
	cb->player = 0;
	cb->nl = 0;
	cb->map.height = 0;
	cb->ewsn[0] = "NO";
	cb->ewsn[1] = "SO";
	cb->ewsn[2] = "WE";
	cb->ewsn[3] = "EA";
}

void	ft_to_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ',' || str[i] == '\t' || str[i] == '\n')
			str[i] = ' ';
}

void	non_printable(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			str[i] = '\0';
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			str[i] = 31;
			break ;
		}
	}
}

void	remove_nl(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			str[i] = '\0';
}

int	check_parameters(char *av)
{
	char	*ext;
	int		i;
	int		j;

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
