/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:26:59 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/13 13:51:05 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "geo.h"
#include "rt.h"
#include "utils.h"

void				add_geometry(t_geo *geo, t_geo **geos)
{
	t_geo			*tmp;

	if (!*geos)
		*geos = geo;
	else
	{
		tmp = *geos;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = geo;
	}
}

int				add_geometry_negative(t_geo *geo, int i, t_geo *neg0)
{
	t_geo		*tmp;

	if (!geo || !neg0)
		return (0);
	else
	{
		tmp = geo;
		while (tmp && i > 0)
		{
			i--;
			tmp = tmp->next;
		}
		if (i == 0 && tmp)
		{
			add_geometry(neg0, &tmp->neg);
			return (1);
		}
	}
	return (0);
}

