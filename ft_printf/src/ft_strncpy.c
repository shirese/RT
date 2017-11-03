/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:33:55 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/08 09:53:32 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	unsigned int index;

	index = 0;
	while (index < n && src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	while (index < n)
	{
		dst[index] = '\0';
		index++;
	}
	return (dst);
}
