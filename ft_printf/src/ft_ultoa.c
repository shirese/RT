/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/18 19:07:12 by chaueur           #+#    #+#             */
/*   Updated: 2014/12/30 15:58:09 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ultoa(unsigned long n)
{
	char				*ret;
	size_t				size;
	unsigned long		x;

	x = n;
	size = 1;
	while ((n = n / 10))
		size++;
	ret = ft_strnew(size);
	if (ret)
	{
		while (size--)
		{
			ret[size] = x % 10 + '0';
			x /= 10;
		}
	}
	return (ret);
}
