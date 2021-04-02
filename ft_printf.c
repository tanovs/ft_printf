/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 20:13:51 by atable            #+#    #+#             */
/*   Updated: 2020/07/14 19:35:02 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			write_chars(va_list ptr, int num, char fl)
{
	int	siz;

	siz = 0;
	if (fl == '-' || num < 0)
	{
		ft_putchar(va_arg(ptr, int));
		return (left_alignment(num, "", 1));
	}
	if (fl == '0')
	{
		siz += right_alignment(num, '0', "", 1);
		ft_putchar(va_arg(ptr, int));
	}
	if (fl == '*')
	{
		siz += right_alignment(num, ' ', "", 1);
		ft_putchar(va_arg(ptr, int));
	}
	return (siz);
}

char		*variables(va_list ptr, char fmt)
{
	char	*str;

	if (fmt == 's')
		str = ft_strdup(va_arg(ptr, char *));
	if (fmt == 'd' || fmt == 'i')
		str = ft_itoa(va_arg(ptr, int));
	if (fmt == 'u')
		str = unsigned_itoa(va_arg(ptr, unsigned int));
	if (fmt == 'p')
		str = hex(va_arg(ptr, unsigned long), 'p');
	if (fmt == 'x')
		str = hex(va_arg(ptr, unsigned int), 'x');
	if (fmt == 'X')
		str = hex(va_arg(ptr, unsigned int), 'X');
	return (str);
}

static void	percent(const char *format, va_list ptr, int *result_len)
{
	t_params p;

	if (*format == '-')
	{
		ft_putchar('%');
		p = print_params(format + 1, ptr);
		*result_len += left_alignment(find_p(p.num, p.w) - 1, "", 0);
	}
	if (*format == '0')
	{
		p = print_params(format + 1, ptr);
		*result_len += right_alignment(find_p(p.num, p.w) - 1, *format, "", 0);
	}
	if (ft_memchr("123456789", *format, 9) || *format == '*')
	{
		p = print_params(format, ptr);
		*result_len += right_alignment(find_p(p.num, p.w) - 1, ' ', "", 0);
	}
	if (*format != '-')
		ft_putchar('%');
}

static char	*moove_str(const char *format, int tmp, int *result, va_list ptr)
{
	if (tmp < 0)
	{
		if (tmp == -3)
		{
			percent(format, ptr, result);
			while (*format != '%')
				format++;
			format++;
			*result += 1;
		}
		else
			ft_putchar('%');
		return ((char *)format);
	}
	*result += tmp;
	if (*format == ' ')
		format++;
	while (ft_memchr("%-0.*123456789", *format, 23))
		format++;
	format++;
	return ((char *)format);
}

int			ft_printf(const char *format, ...)
{
	int		result_len;
	va_list	ptr;

	if (!format)
		return (-1);
	va_start(ptr, (char *)format);
	result_len = 0;
	while (*format)
	{
		if (*format == '%')
			format = moove_str(format + 1, parse(format + 1, ptr),
					&result_len, ptr);
		else
		{
			ft_putchar(*(format++));
			result_len++;
		}
	}
	va_end(ptr);
	return (result_len);
}
