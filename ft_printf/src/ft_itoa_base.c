/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 18:39:56 by chaueur           #+#    #+#             */
/*   Updated: 2015/01/23 19:05:03 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base(long long n, int base)
{
	static char		buf[INT_DIGITS + 2];
	char			*ret;
	int				neg;

	if (base < 0)
		return (NULL);
	ret = buf + INT_DIGITS + 1;
	if (n == 0 && (*--ret = '0'))
		return (ret);
	neg = 0;
	if (n < 0)
		neg = 1;
	while (n != 0)
	{
		if (base > 10 && n % base >= 10 && n % base <= 15)
			*--ret = 'a' + n % base - 10;
		else if (n > 0)
			*--ret = '0' + n % base;
		else
			*--ret = '0' - n % base;
		n /= base;
	}
	(neg) ? (*--ret = '-') : 0;
	return (ret);
}
