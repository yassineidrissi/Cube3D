/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:34:13 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/20 12:06:04 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRCS_H
# define SRCS_H
# include <stdarg.h>
# include "../cube3d.h"

void        handl_errors(int i);
char        *ft_itoa(int n);
int        ft_printf(const char *format, ...);
char       **ft_split(const char *s, char c);
char       *ft_strdup(const char *s1);
int        ft_cmp(const char *s1, const char *s2);
void       ft_free_double(char **p);
int        ft_strlen(char *s);

#endif