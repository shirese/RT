/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 10:45:25 by chaueur           #+#    #+#             */
/*   Updated: 2014/12/29 10:45:27 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_uitoa(unsigned int n)
{
	char			*ret;
	size_t			size;
	unsigned int	x;

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
