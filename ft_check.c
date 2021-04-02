/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:56:36 by atable            #+#    #+#             */
/*   Updated: 2020/07/11 11:36:33 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		find_p(int a, int b)
{
	if (a == -1)
		return (b);
	return (a);
}

int		precision_null(t_params par)
{
	if (find_p(par.num, par.w) == 1)
		ft_putchar('(');
	if (find_p(par.num, par.w) == 2)
		ft_putstr("(n");
	if (find_p(par.num, par.w) == 3)
		ft_putstr("(nu");
	if (find_p(par.num, par.w) == 4)
		ft_putstr("(nul");
	if (find_p(par.num, par.w) == 5)
		ft_putstr("(null");
	if (find_p(par.num, par.w) > 5 || find_p(par.num, par.w) < 0)
	{
		ft_putstr("(null)");
		return (6);
	}
	return (find_p(par.num, par.w));
}

int		num_null(int num, char fl)
{
	int siz;

	siz = 0;
	if (fl == '*')
		siz += right_alignment(num - 6, ' ', "", 0);
	ft_putstr("(null)");
	siz += ft_strlen("(null)");
	if (fl == '-')
		siz += left_alignment(num - 6, "", 0);
	return (siz);
}

char	*null_str(char *str, long int num, char fmt)
{
	if (num == 0 && fmt != 'p')
		str[0] = '0';
	if (fmt == 'p')
	{
		str[0] = '0';
		str[1] = 'x';
		if (num == 0)
			str[2] = '0';
	}
	return (str);
}

int		check_str(const char *str, char *fmt)
{
	size_t i;

	i = 0;
	while (ft_memchr("-0.*123456789", str[i], 13))
		i++;
	*fmt = str[i];
	if (!ft_memchr("csdiupxX%", *fmt, 9))
		return (-2);
	if (*fmt == '%')
		return (-3);
	return (0);
}
