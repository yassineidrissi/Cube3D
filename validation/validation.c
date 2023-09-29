/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:57:01 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/29 10:57:07 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
/* chek bol to see if there is something other than NO SO WE EA F C before arriving to the map*/
void	check_bol(t_cub3D *cb)
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
void	check_repeat(t_cub3D *cb)
{
	int	i;

	i = -1;
	while (cb->joined_map && cb->joined_map[++i])
	{
		if (cb->joined_map[i] == 'N' || cb->joined_map[i] == 'S'
			|| cb->joined_map[i] == 'W' || cb->joined_map[i] == 'E')
			cb->player++;
		else if (cb->joined_map[i] != '1' && cb->joined_map[i] != '0'
			&& cb->joined_map[i] != ' ' && cb->joined_map[i] != '\t'
			&& cb->joined_map[i] != '\n')
		{
			free(cb->joined_map);
			handl_errors(10);
		}
	}
	if (cb->player != 1)
	{
		free(cb->joined_map);
		handl_errors(10);
	}
}

/* store player position and check if 0 or player are surrounded by other than 1 and 0  */
//! when i put the player  to W character the forme of the player is changed we need to check this errurs
int	p_or_z(t_cub3D *cb, char c, int x, int y)
{
	if (c == '0')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		cb->p.x = x * T_S + (T_S / 2);
		cb->p.y = y * T_S + (T_S / 2);
		if (c == 'N')
			cb->angle = (3 * M_PI) / 2;
		else if (c == 'S')
			cb->angle = M_PI / 2;
		else if (c == 'E')
			cb->angle = 0;
		else if (c == 'W')
			cb->angle = M_PI;
		return (1);
	}
	return (0);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	ft_count_quote(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == ',')
			count++;
	if (count != 2)
	{
		free(str);
		handl_errors(10);
	}
}
