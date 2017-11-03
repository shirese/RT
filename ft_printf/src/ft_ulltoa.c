/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 12:58:02 by chaueur           #+#    #+#             */
/*   Updated: 2014/12/30 14:00:16 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ulltoa(long long unsigned int n)
{
	char					*ret;
	size_t					size;
	long long unsigned int	x;

	size = 1;
	x = n;
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
