/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:34:13 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/21 16:32:18 by zouaraqa         ###   ########.fr       */
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
char		*ft_strcpy(char *dst, char *src);
int         ft_atoi(const char *str);
char	*ft_strjoin(char *s1, char *s2);

#endif