/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:39:32 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/08 10:43:13 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_convert_rest(char *str, double n, size_t prec, int dot)
{
	size_t		i;

	i = 0;
	while (dot--)
	{
		n *= 10;
		*str = (int)n + '0';
		str++;
		n -= (int)n;
	}
	if (prec > 0)
	{
		*str = '.';
		str++;
		while (i++ < prec)
		{
			n *= 10;
			*str = (int)n + '0';
			str++;
			n -= (int)n;
		}
	}
	*str = '\0';
}

static int		ft_str_size(double n, size_t precision)
{
	int			len;
	int			dot;

	len = 0;
	dot = 0;
	if (n > -1 && n < 1)
		len++;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n >= 1)
	{
		len++;
		n /= 10;
	}
	if (precision > 0)
		len++;
	len += precision;
	return (len);
}

static void		ft_convert(char *str, double n, size_t precision)
{
	double		n_tmp;
	int			dot;

	n_tmp = n;
	dot = 0;
	if (n < 0)
	{
		n_tmp = n;
		n = -n;
		*str = '-';
		str++;
	}
	if (n_tmp > -1 && n_tmp < 1)
	{
		*str = '0';
		str++;
	}
	while (n >= 1 && dot++ >= 0)
		n /= 10;
	ft_convert_rest(str, n, precision, dot);
}

char			*ft_ftoa(double n, size_t precision)
{
	char		*str;

	str = NULL;
	str = (char *)malloc(sizeof(*str) * ft_str_size(n, precision) + 1);
	if (str)
		ft_convert(str, n, precision);
	return (str);
}
