/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:32:20 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/21 08:02:46 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "./../cube3d.h"

// void  int_map(t_cube3d *cb);
// void init_cube3d(t_cube3d *cb);
// int check_pameters
int check_parameters(char *av);
int	fill_type(t_cube3d *cb);

#endif