/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 18:06:24 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/10 19:18:33 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*tmp_dst;
	char	*tmp_src;
	char	stop;

	stop = (unsigned char)c;
	tmp_dst = dst;
	tmp_src = (char*)src;
	while (n)
	{
		if (*tmp_src == stop)
		{
			*tmp_dst++ = *tmp_src++;
			return (tmp_dst);
		}
		n--;
		*tmp_dst++ = *tmp_src++;
	}
	return (NULL);
}
