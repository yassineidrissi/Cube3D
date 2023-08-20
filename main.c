/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/20 12:37:52 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int main(int ac, char **av)
{
    t_cube3d cb;

    if (ac != 2)
        handl_errors(10);
    cb.fd = open(av[1], O_RDONLY);
    if ((cb.fd == -1 ) || check_parameters(av[1]) == 0 )
        handl_errors(6);
    init_cube3d(&cb);
    
    cb.map.map[20][20] = 48;
    ft_printf("Hello World! %c\n", cb.map.map[20][20]);
    return 0;
}