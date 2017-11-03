/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 12:02:42 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/10 19:11:17 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dst_len;
	size_t			tmp_size;
	char			*tmp_dst;
	const char		*tmp_src;

	tmp_dst = dst;
	tmp_src = src;
	tmp_size = size;
	while (*tmp_dst != '\0' && tmp_size-- != 0)
		tmp_dst++;
	dst_len = tmp_dst - dst;
	tmp_size = size - dst_len;
	if (tmp_size == 0)
		return (dst_len + ft_strlen(src));
	while (*tmp_src != '\0')
	{
		if (tmp_size != 1)
		{
			*tmp_dst++ = *tmp_src;
			tmp_size--;
		}
		tmp_src++;
	}
	*tmp_dst = '\0';
	return (dst_len + (tmp_src - src));
}
