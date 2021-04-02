/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 12:20:15 by atable            #+#    #+#             */
/*   Updated: 2020/07/14 19:29:46 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			precision(const char *str, va_list ptr, char fmt, t_params tmp)
{
	t_params	par;
	int			siz;
	char		*result;

	if (tmp.prev == -1)
		par = print_params(str, ptr);
	else
		par = tmp;
	if (fmt == 'p' && find_p(par.num, par.w) == 0)
		return (alligment(3, fmt, ptr, '-'));
	if (fmt == 'c')
		return (write_chars(ptr, par.prev, ' '));
	if (!(result = variables(ptr, fmt)) && fmt != 's')
		return (-1);
	if (!result && fmt == 's')
		return (precision_null(par));
	if (find_p(par.num, par.w) < 0)
	{
		siz = right_alignment(par.prev, ' ', result, ft_strlen(result));
		free(result);
		return (siz);
	}
	if (ft_memchr("diuxX", fmt, 5))
		return (not_str_precision(par, ft_strlen(result), result));
	return (str_precision(par, ft_strlen(result), result));
}

static int	print_minus_flag(const char *str, va_list ptr, char fmt)
{
	t_params	par;
	int			tmp;

	tmp = 0;
	while (*str == '-')
		str++;
	par = print_params(str, ptr);
	if (par.w < 0 && par.num == -1)
		par.w *= (-1);
	if (par.num == 0 && !par.i && *str != '.')
		return (alligment(par.num, fmt, ptr, '-'));
	if (par.num == 0 && !par.i && *str == '.')
		return (precision(++str, ptr, fmt, par));
	if (*(str + par.i) == '.')
	{
		tmp = precision(str + par.i + 1, ptr, fmt, par);
		return (left_alignment(find_p(par.num, par.w) - tmp, "", 0) + tmp);
	}
	return (alligment(find_p(par.num, par.w), fmt, ptr, '-'));
}

int			print_num_flag(const char *str, va_list ptr, char fmt)
{
	t_params	par;
	char		fl;
	int			siz;

	fl = '*';
	siz = 0;
	par = print_params(str, ptr);
	str = str + par.i;
	if (ft_memchr("csduipxX", *str, 8) && find_p(par.num, par.w) >= 0)
		return (alligment(find_p(par.num, par.w), fmt, ptr, fl));
	if (ft_memchr("csduipxX", *str, 8) && find_p(par.num, par.w) < 0)
		return (alligment(0 - find_p(par.num, par.w), fmt, ptr, '-'));
	par = help_fun(par, ++str, ptr);
	if (par.prev >= 0)
		return (positive_num(str, ptr, fmt, par));
	else
	{
		if (fmt == 'p')
			siz = alligment(0 - par.prev, fmt, ptr, '-') + siz;
		if (fmt != 'p')
			siz = precision(str, ptr, fmt, par) + siz;
		siz += left_alignment(0 - par.prev - siz, "", 0);
	}
	return (siz);
}

static int	print_zero_flag(const char *str, va_list ptr, char fmt)
{
	t_params	par;
	int			tmp;
	char		fl;

	fl = '0';
	if (fmt == 's')
		fl = '*';
	if ((tmp = noname_func(str, ptr, fmt)) != -1)
		return (tmp);
	par = print_params(str, ptr);
	if (find_p(par.w, par.num) < 0)
		fl = '-';
	if (par.num == 0 && !par.i)
		return (alligment(par.num, fmt, ptr, '0'));
	if (par.num == 0 && par.i == -1)
	{
		if (*str == '-')
			return (print_minus_flag(++str, ptr, fmt));
		return (precision(++str, ptr, fmt, par));
	}
	if (*(str + par.i) == '*')
		return (-1);
	if (find_p(par.w, par.num) < 0)
		return (alligment(0 - find_p(par.w, par.num), fmt, ptr, fl));
	return (alligment(find_p(par.w, par.num), fmt, ptr, fl));
}

int			parse(const char *s, va_list ptr)
{
	char		fmt;
	t_params	p;

	p.i = -1;
	p.num = -1;
	p.prev = -1;
	p.w = -1;
	fmt = '\0';
	if (*s == ' ')
		ft_putchar(*(s++));
	if (check_str(s, &fmt))
		return (check_str(s, &fmt));
	if (*s == '-')
		return (print_minus_flag(++s, ptr, fmt));
	if (*s == '.')
		return (precision(++s, ptr, fmt, p));
	if (*s == '0')
		return (print_zero_flag(++s, ptr, fmt));
	if (*s == '*' || (*s >= '0' && *s <= '9'))
		return (print_num_flag(s, ptr, fmt));
	return (alligment(0, fmt, ptr, '-'));
}
