/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 00:02:00 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/26 00:08:54 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "../cube3d.h"

int check_wall(t_cube3d *cb);
int draw_player(t_cube3d *cb, int angle, int playerSize, int angle_vue);
int if_player(char c);
void draw_map(t_cube3d *cb);
void change_player(t_cube3d *cb, int KEY);
void draw_C_F(t_cube3d *cb);

#endif