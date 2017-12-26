/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 18:39:56 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/09 10:43:06 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		itoa_size(long long n, int base)
{
	size_t			ret;

	ret = 0;
	while (n != 0)
	{
		n /= base;
		ret++;
	}
	return (ret);
}

static char			ft_itoa_norme(long long n, int base)
{
	if (base > 10 && n % base >= 10 && n % base <= 15)
		return ('a' + n % base - 10);
	else if (n > 0)
		return ('0' + n % base);
	else
		return ('0' - n % base);
}

char				*ft_itoa_base(long long n, int base)
{
	char			*ret;
	int				i;
	int				len;
	int				neg;

	if (base < 0)
		return (NULL);
	i = 1;
	len = itoa_size(n, base);
	neg = 0;
	if (n < 0 && len++)
		neg = 1;
	ret = malloc(sizeof(char) * len + 1);
	if (n == 0 && !ret)
		return (NULL);
	while (n != 0)
	{
		ret[len - (i++)] = ft_itoa_norme(n, base);
		n /= base;
	}
	(neg) ? (ret[len - (++i)] = '-') : 0;
	ret[len] = '\0';
	return (ret);
}
