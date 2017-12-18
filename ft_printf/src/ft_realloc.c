/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:52:05 by chaueur           #+#    #+#             */
/*   Updated: 2017/04/27 12:40:59 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*p;

	if (!ptr)
		return (ft_memalloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	if (!(p = ft_memalloc(new_size)))
		return (NULL);
	ft_memcpy(p, ptr, old_size);
	free(ptr);
	ptr = NULL;
	return (p);
}
