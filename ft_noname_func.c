/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noname_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:34:33 by atable            #+#    #+#             */
/*   Updated: 2020/07/14 19:35:05 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	noname_func(const char *str, va_list ptr, char fmt)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		while (!(ft_memchr("csdiupxX", str[i], 8)))
			if (str[i++] == '.')
				return (print_num_flag(str, ptr, fmt));
	return (-1);
}
