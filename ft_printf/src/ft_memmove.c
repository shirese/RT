/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:00:14 by chaueur           #+#    #+#             */
/*   Updated: 2016/12/16 14:44:03 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;

	tmp_dst = dst;
	tmp_src = src;
	if (src <= dst)
	{
		tmp_dst += (len - 1);
		tmp_src += (len - 1);
		while (len--)
			*tmp_dst-- = *tmp_src--;
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
