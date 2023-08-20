/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:32:10 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/20 08:58:20 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../cube3d.h"

typedef struct l_get
{
	int		indx;
	char	*data;
	char	*line;
	char	*part;
}t_get;

char	*get_next_line(int fd);
char	*ft_my_strjoin(char *src, char *mot, int a);
char	*ft_my_substr(char *s, int start, int len, int free_or_not);
char	*ft_calloc(int count, int size);
int		ft_strchr(char *str);
void	ft_free_str(char **p);

#endif