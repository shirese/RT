/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 18:22:43 by chaueur           #+#    #+#             */
/*   Updated: 2014/12/02 19:03:39 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(t_coord *coord, size_t coord_size)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return (0);
	if (tmp)
	{
		if (coord == NULL)
		{
			tmp->coord = NULL;
			tmp->coord_size = 0;
		}
		else
		{
			tmp->coord = malloc(coord_size);
			if (!tmp->coord)
				return (NULL);
			ft_memcpy((tmp->coord), coord, (coord_size));
			tmp->coord_size = coord_size;
		}
		tmp->next = NULL;
	}
	return (tmp);
}
