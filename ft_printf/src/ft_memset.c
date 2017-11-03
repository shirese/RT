/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:15:44 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/08 09:56:47 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char *tmp_b;

	tmp_b = b;
	while (len)
	{
		*tmp_b = c;
		len--;
		tmp_b++;
	}
	return (b);
}
