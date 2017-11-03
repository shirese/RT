/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsig_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 15:55:24 by chaueur           #+#    #+#             */
/*   Updated: 2015/01/22 16:36:42 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_unsig_base(unsigned long long n, int base)
{
	static char		buf[INT_UNS_DIGITS + 2];
	char			*ret;

	if (base < 0)
		return (NULL);
	ret = buf + INT_UNS_DIGITS + 1;
	if (n == 0)
	{
		*--ret = '0';
		return (ret);
	}
	while (n != 0)
	{
		if (base > 10 && n % base >= 10 && n % base <= 15)
			*--ret = 'a' + n % base - 10;
		else
			*--ret = '0' + n % base;
		n /= base;
	}
	return (ret);
}
