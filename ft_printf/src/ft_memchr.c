/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 18:41:31 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/10 19:06:58 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*tmp_s;
	unsigned char			target;

	tmp_s = s;
	target = (unsigned char)c;
	if (n != 0)
	{
		while (n--)
		{
			if (*tmp_s++ == target)
				return ((void *)(tmp_s - 1));
		}
	}
	return (NULL);
}
