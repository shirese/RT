/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 10:00:06 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/10 19:33:03 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*tmp_s1;
	const unsigned char		*tmp_s2;

	tmp_s1 = (const unsigned char *)s1;
	tmp_s2 = (const unsigned char *)s2;
	if (!tmp_s1 || !tmp_s2)
		return (0);
	while (n)
	{
		if (*tmp_s1 != *tmp_s2)
			return ((unsigned char)*tmp_s1 - (unsigned char)*tmp_s2);
		tmp_s1++;
		tmp_s2++;
		n--;
	}
	return (0);
}
