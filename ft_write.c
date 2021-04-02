/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atable <atable@student.school-21.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:22:47 by atable            #+#    #+#             */
/*   Updated: 2020/07/14 19:32:57 by atable           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	size_t i;

	i = 0;
	if (s[i])
	{
		while (s[i] != '\0')
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			n *= (-1);
			ft_putchar('-');
		}
		if (n < 10)
			ft_putchar(n + '0');
		else
		{
			ft_putnbr(n / 10);
			ft_putchar(n % 10 + '0');
		}
	}
}

int		str_precision(t_params par, size_t len, char *result)
{
	int		siz;
	size_t	i;
	int		param;

	siz = 0;
	i = 0;
	param = find_p(par.num, par.w);
	if (param < 0 && par.num == -1)
		param = len;
	if (param > (int)len && par.prev >= param)
		siz += right_alignment(param - len, ' ', "", 0);
	else if ((param > (int)len && par.prev > (int)len))
		siz += right_alignment(par.prev - len, ' ', "", 0);
	while (result[i] != '\0' && param-- > 0)
	{
		ft_putchar(result[i]);
		i++;
	}
	free(result);
	return (siz + i);
}

int		not_str_precision(t_params par, size_t len, char *result)
{
	int	siz;

	siz = 0;
	if (par.prev >= 0)
	{
		if (find_p(par.w, par.num) == 0 && len == 1 && *result == '0')
			siz += right_alignment(par.prev, ' ', "", 0);
		else if (find_p(par.w, par.num) < (int)len)
			siz += right_alignment(par.prev - len, ' ', "", 0);
		else
		{
			if (*result == '-')
				par.prev--;
			siz += right_alignment(par.prev - find_p(par.w, par.num),
					' ', "", 0);
		}
	}
	if (find_p(par.w, par.num) == 0 && len == 1 && *result == '0')
		*result = 0;
	siz += right_alignment(find_p(par.w, par.num), '.', result,
			ft_strlen(result));
	free(result);
	return (siz);
}
