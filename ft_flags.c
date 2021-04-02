/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 21:14:21 by atable            #+#    #+#             */
/*   Updated: 2020/07/11 13:31:25 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			left_alignment(int num, char *str, int len)
{
	if (num <= 0 && *str == '\0' && len == 0)
		return (0);
	ft_putstr(str);
	while (len < num)
	{
		ft_putchar(' ');
		len++;
	}
	return (len);
}

int			right_alignment(int num, char sym, char *str, int len)
{
	size_t i;

	i = 0;
	if (num <= 0 && *str == '\0' && len == 0)
		return (0);
	if (*str == '-' && (sym == '0' || sym == '.'))
	{
		ft_putchar(str[0]);
		i++;
		if (sym == '.')
			num++;
	}
	if (sym == '.')
		sym = '0';
	while (len++ < num)
		ft_putchar(sym);
	if (!str)
	{
		ft_putstr("(null)");
		return (len - 1);
	}
	ft_putstr(&str[i]);
	return (len - 1);
}

int			alligment(int num, char fmt, va_list ptr, char fl)
{
	char	*str;
	int		siz;

	siz = 0;
	if (fmt == 'c')
		return (write_chars(ptr, num, fl));
	if (!(str = variables(ptr, fmt)) && fmt != 's')
		return (-1);
	if (!str && fmt == 's')
		return (num_null(num, fl));
	if (num < 0 && fl == '0')
	{
		num *= (-1);
		fl = '-';
	}
	if (fl == '-')
		siz += left_alignment(num, str, ft_strlen(str));
	if (fl == '0')
		siz += right_alignment(num, '0', str, ft_strlen(str));
	if (fl == '*')
		siz += right_alignment(num, ' ', str, ft_strlen(str));
	if (*str == '\0' && fmt == 'c')
		siz++;
	free(str);
	return (siz);
}

t_params	help_fun(t_params par, const char *str, va_list ptr)
{
	int	tmp;

	tmp = find_p(par.num, par.w);
	par = print_params(str, ptr);
	par.prev = tmp;
	return (par);
}

int			positive_num(const char *str, va_list ptr, char fmt, t_params par)
{
	int siz;

	siz = 0;
	if (fmt != 'c' && fmt != 's' && fmt != 'p')
		return (precision(++str, ptr, fmt, par));
	if (fmt == 'p')
		siz += alligment(par.prev, fmt, ptr, '*') + siz;
	else if (find_p(par.num, par.w) >= 0)
		siz += right_alignment(par.prev - find_p(par.num, par.w), ' ', "", 0);
	if (fmt != 'p')
		siz = precision(str, ptr, fmt, par) + siz;
	return (siz);
}
