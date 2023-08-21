/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 06:42:51 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/21 08:45:05 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs.h"

int	ft_atoi(const char *str)
{
	int							i;
	unsigned long long int		n;

	i = 0;
	n = 0;
	if (str[0] == '0' && !str[1])
		return (0);
	while (str[i] <= '9' && str[i] >= '0')
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	printf("======>str = [%s] and n = %llu and str[i] = %c\n", str, n, str[i]);
	if (str[i])
		return (-1);
	printf("n = %llu\n", n);
	// if (n > MAX_INT || n < MIN_INT)
	// 		return (-1);
	return ((int)n);
}

// int	main(int	ac, char	**av)
// {
// 	printf("%d\n", ft_atoi(av[1]));
// 	printf("%d\n", atoi(av[1]));
// }