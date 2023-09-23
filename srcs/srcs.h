/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:34:13 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/23 15:26:58 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRCS_H
# define SRCS_H
# include <stdarg.h>
# include "../cub3D.h"

char	**ft_split(const char *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *s1, char *set, int fre);
char	*ft_itoa(int n);
void	non_printable(char *str);
void	ft_free_double(char **p);
void	handl_errors(int i);
int		ft_cmp(const char *s1, const char *s2);
int		ft_printf(const char *format, ...);
int		ft_atoi(const char *str);
int		ft_strlen(char *s);

#endif