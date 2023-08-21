/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/21 08:52:30 by yaidriss         ###   ########.fr       */
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
		printf ("j = %zu, k = %zu cb->text->cnt %s\n", j, k,cb->text->cnt[0]);
		if (!cb->text->cnt[0][j] && !s2[i][k])
		{
			cb->text[i].bol++;
			printf("i=[%zu]  bol = %d\n",i, cb->text->bol);
			if (cb->text[i].bol != 1)
				return (1);
			else
			{
				cb->text[i].path = ft_strdup(cb->text->cnt[1]);
				printf("bol %d,i = %zu,\npath = %s\n",cb->text[i].bol,i,cb->text[i].path);
			}
			return (0);
		}
		i++;
		printf("-------------------------------------------\n");
	}
	return (1);
}

void ft_tab_to_space(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\t' || str[i] == '\n')
			str[i] = ' ';
}

void ft_com_to_space(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == ',' || str[i] == '\n')
			str[i] = ' ';
}

// void fill_texture_img(t_cube3d *cb)
// {
// 	int i;

// 	i = -1;
// 	while (cb->text[++i].path)
// 	{
// 		cb->text[i].img = mlx_xpm_file_to_image(cb->mlx, cb->text[i].path, &cb->text[i].width, &cb->text[i].height);
// 		if (!cb->text[i].img)
// 			handl_errors(6);
// 		cb->text[i].addr = mlx_get_data_addr(cb->text[i].img, &cb->text[i].bits_per_pixel, &cb->text[i].line_length, &cb->text[i].endian);
// 	}
// }

void	fill_texture(t_cube3d *cb)
{
	int	i;

	i = 0;
	ft_tab_to_space(cb->line);//*if there is a tab we replace it with space
	cb->text->cnt = ft_split(cb->line, ' ');//  or split tab too 
	while (cb->text->cnt[i])
		i++;
	if (i != 2 || compare(cb))
	{
		ft_free_double(cb->text->cnt);
		printf("im here\n");
		handl_errors(10);
	}
	// fill_texture_img(cb);
	// int i = -1;
	// while (cb->text[++i].path)
		// printf("########[");

	// printf("[%s]   [%s]\n",cb->text->cnt[0], cb->text->cnt[1]);
	// mlx_texture_t* texture = mlx_load_png(cb->text->cnt[1]);
	// if (!texture)
    //     handl_errors(6);
	// pause();
	// printf("text %s\n", cb->line);
}

void ft_fill_color(t_cube3d *cb, char **RGB, int i)
{
	int j;

	j = 0;
	while (RGB[j])
		j++;
	if (j != 4)
		handl_errors(10);
	printf("*********************\n");
	printf("RGB[1] = %s\n", RGB[1]);
	printf("RGB[2] = %s\n", RGB[2]);
	printf("RGB[3] = %s\n", RGB[3]);
	cb->colors[i].r = ft_atoi(RGB[1]);
	cb->colors[i].g = ft_atoi(RGB[2]);
	cb->colors[i].b = ft_atoi(RGB[3]);
	cb->colors[i].bol++;
	printf("r = %d, g = %d, b = %d\n",cb->colors[i].r, cb->colors[i].g, cb->colors[i].b);

}

void	fill_colors(t_cube3d *cb)
{
	char **RGB;
	int i;
	int j;

	i = 0;
	j = 0;
	ft_tab_to_space(cb->line);
	ft_com_to_space(cb->line);
	RGB = ft_split(cb->line, ' ');	
	printf("color %s\n", cb->line);
	printf("LRGB[%d] = %s\n", i, RGB[i]);
	if (RGB[0][0] == 'F' && !RGB[0][1] && i < 4)
		ft_fill_color(cb, RGB, F);
	else if (RGB[0][0] == 'C' && !RGB[0][1] && i < 4)
		ft_fill_color(cb, RGB, C);
	else
	{
		ft_free_double(RGB);
		handl_errors(1);
	}
	ft_free_double(RGB);
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
	{
		fill_texture(cb);
		printf("im in fill_type\n");
	}
	else if (cb->line[i] == 'F' || cb->line[i] =='C')
		fill_colors(cb);
	else if (cb->line[i] == '1')
		fill_map(cb);
	// else if (cb->line[i] != '\n')
		// handl_errors(10);
	return (0);
}

int	check_content(t_cube3d *cb)
{
	cb->line = NULL; // creat a fun to INIT all
	cb->text[NO].bol = 0;
	cb->text[SO].bol = 0;
	cb->text[WE].bol = 0;
	cb->text[EA].bol = 0;
	cb->colors[F].bol = 0;
	cb->colors[C].bol = 0;
	cb->line = get_next_line(cb->fd);
	while (cb->line)
	{
		if (fill_type(cb))
		{
			printf("im here check inside if fill_type\n");
			free(cb->line);
			handl_errors(6);
		}
		// printf("check line = %s\n", cb->line);
		// printf("line = %s\n", cb->line);
		free(cb->line);
		cb->line = get_next_line(cb->fd);
	}
	// close(cb->fd);
	free(cb->line);
	if (cb->text[0].bol != 1 || cb->text[1].bol != 1 || cb->text[2].bol != 1 ||cb->text[3].bol != 1 || cb->colors[F].bol != 1 || cb->colors[C].bol != 1)
	{
		printf("bol F = %d, bol C = %d\n", cb->colors[F].bol, cb->colors[C].bol);
		handl_errors(10);
	}
	// printf("im finaly here\n");
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
    
	int i = 0;
	while(cb.colors[i].bol == 1)
	{
		printf("r = %d, g = %d, b = %d . i %d\n",cb.colors[i].r, cb.colors[i].g, cb.colors[i].b, i);
		i++;
	}
    ft_printf("Hello World! %c\n", cb.map.map[20][20]);
    return 0;
}