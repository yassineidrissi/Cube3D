/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/20 17:47:49 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	compare(t_cube3d *cb)
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
		while (cb->text->cnt[0][j] && cb->text->cnt[0][j] == s2[i][k])
		{
			j++;
			k++;
		}
		if (!cb->text->cnt[0][j] && !s2[i][k])
		{
			cb->text[i].bol++;
			printf("i=[%zu]  bol = %d\n",i, cb->text->bol);
			if (cb->text[i].bol != 1)
				return (1);
			else
				cb->text[i].path = ft_strdup(cb->text->cnt[1]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	fill_texture(t_cube3d *cb)
{
	cb->text->cnt = ft_split(cb->line, ' ');//  or split tab too
	cb->text->cnt[1][ft_strlen(cb->text->cnt[1]) - 1] = '\0';
	if (compare(cb))
	{
		ft_free_double(cb->text->cnt);
		handl_errors(6);
	}

	// int i = -1;
	// while (cb->text[++i].path)
	// 	printf("########[%s] %d   \n",cb->text[0].path, i);

	// printf("[%s]   [%s]\n",cb->text->cnt[0], cb->text->cnt[1]);
	mlx_texture_t* texture = mlx_load_png(cb->text->cnt[1]);
	if (!texture)
        handl_errors(6);
	// pause();
	// printf("text %s\n", cb->line);
}

void	fill_color(t_cube3d *cb)
{
	// printf("color %s\n", cb->line);
}
void	fill_map(t_cube3d *cb)
{
	// return ;
	// printf("map %s\n", cb->line);
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

int	check_content(t_cube3d *cb)
{
	cb->line = NULL; // creat a fun to INIT all
	cb->text[NO].bol = 0;
	cb->text[SO].bol = 0;
	cb->text[WE].bol = 0;
	cb->text[EA].bol = 0;
	cb->line = get_next_line(cb->fd);
	while (cb->line)
	{
		if (fill_type(cb))
		{
			free(cb->line);
			handl_errors(6);
		}
		free(cb->line);
		cb->line = get_next_line(cb->fd);
	}
	free(cb->line);
	return (0);
}

int main(int ac, char **av)
{
    t_cube3d cb;

    if (ac != 2)
        handl_errors(10);
    cb.fd = open(av[1], O_RDONLY);
    if (cb.fd == -1 || check_parameters(av[1]) == 0 || check_content(&cb))
        handl_errors(6);
    // init_cube3d(&cb);
    
    cb.map.map[20][20] = 48;
    ft_printf("Hello World! %c\n", cb.map.map[20][20]);
    return 0;
}