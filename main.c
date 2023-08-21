/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/21 13:08:45 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*####  function are in validation dir  #####*/
int main(int ac, char **av)
{
    t_cube3d cb;

    if (ac != 2)
        handl_errors(10);
    init_cube3d(&cb);
    cb.fd = open(av[1], O_RDONLY);
    if (cb.fd == -1 || check_parameters(av[1]) == 0 || check_content(&cb))
        handl_errors(6);
    
	int i = 0;
	while(cb.colors[i].bol == 1)
	{
		printf("r = %d, g = %d, b = %d . i %d\n",cb.colors[i].r, cb.colors[i].g, cb.colors[i].b, i);
		i++;
	}
	system("leaks cub3D");
    return 0;
}