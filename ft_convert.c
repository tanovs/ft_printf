/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 18:29:38 by atable            #+#    #+#             */
/*   Updated: 2020/07/11 12:59:07 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*flip_line(char *str, long int num, char sym, size_t i)
{
	char	tmp;

	while ((num /= 16) > 0)
	{
		if (num % 16 < 10)
			str[i++] = num % 16 + '0';
		else
		{
			str[i++] = num % 16 + 87;
			if (sym == 'X')
				str[i - 1] = ft_toupper(str[i - 1]);
		}
	}
	i = 0;
	if (sym == 'p')
		str = str + 2;
	while (i < (ft_strlen(str) / 2))
	{
		tmp = str[i];
		str[i] = str[ft_strlen(str) - i - 1];
		str[ft_strlen(str) - i++ - 1] = tmp;
	}
	if (sym == 'p')
		str = str - 2;
	return (str);
}

char		*hex(long int num, char sym)
{
	char		*str;
	long int	n;
	size_t		i;

	n = num;
	i = 0;
	while ((n /= 16) > 0)
		i++;
	if (sym == 'p')
		i += 2;
	if (!(str = (char *)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	str[i + 1] = '\0';
	if (num == 0 || (num == 0 && sym == 'p'))
		return (null_str(str, num, sym));
	if (sym == 'p')
		str = null_str(str, num, sym);
	i = 0;
	if (sym == 'p')
		i = 2;
	return (flip_line(str, num * 16, sym, i));
}

char		*unsigned_itoa(unsigned int n)
{
	unsigned int	tmp;
	char			*str;
	size_t			i;

	tmp = n;
	i = 0;
	while ((tmp /= 10) > 0)
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	str[i + 1] = 0;
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

static int	find_num(const char *s, int *num)
{
	int	i;

	i = -1;
	if (ft_memchr("scduipxX", s[0], 8) || s[0] == '.')
		return (0);
	if (!(s[0] >= '0' && s[0] <= '9'))
		return (-1);
	while (s[++i] >= '0' && s[i] <= '9')
		*num = (*num + s[i] - '0') * 10;
	return (i);
}

t_params	print_params(const char *str, va_list ptr)
{
	t_params	params;
	int			i;
	int			num;

	num = 0;
	i = find_num(str, &num);
	params.i = i;
	params.num = num / 10;
	params.w = -1;
	params.prev = -1;
	if (i == -1 && *str == '*')
	{
		params.i = 1;
		params.num = -1;
		params.w = va_arg(ptr, int);
	}
	return (params);
}
