/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:26:59 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/28 15:45:18 by chaueur          ###   ########.fr       */
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

int					add_geometry_negative(t_geo *geo, int i, t_geo *neg0)
{
	t_geo			*tmp;

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

t_vec3				plane_norm(t_geo *geo)
{
	t_plane *plane;

	plane = (t_plane*)geo->curr;
	return (plane->normal);
}

t_vec3				negative_norm(t_geo *geo, t_hp hp)
{
	if (geo->type == 1)
		return (plane_norm(geo));
	if (geo->type == 2)
		return (cone_norm(geo, hp.p));
	else if (geo->type == 3)
		return (cylinder_norm(geo, hp));
	else if (geo->type == 4)
		return (sphere_norm(geo, hp.p));
	else if (geo->type == 5)
		return (disk_norm(geo));
	else if (geo->type == 6)
		return (para_norm(geo, hp.p));
	return (vec3_stack(0.0, 0.0, 0.0));
}
