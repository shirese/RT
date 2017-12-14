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

t_hp				(*g_get_obj_collider(int id))(t_geo *geo, t_ray r)
{
	if (id == 1)
		return (hit_plane);
	if (id == 2)
		return (hit_cone);
	if (id == 3)
		return (hit_cylinder);
	if (id == 4)
		return (hit_sphere);
	if (id == 5)
		return (hit_disk);
	if (id == 6)
		return (hit_paraboloid);
	return (NULL);
}

static int			setup_geo_mater(t_geo **geo)
{
	(*geo)->mater = malloc(sizeof(t_mater));
	if (!(*geo)->mater)
	{
		free((*geo)->origin);
		free((*geo));
		return (0);
	}
	(*geo)->mater->kd = color_new_stack(0., 0., 0.);
	(*geo)->mater->ks = color_new_stack(0., 0., 0.);
	(*geo)->mater->ns = 32.;
	(*geo)->mater->illum = 1;
	(*geo)->mater->ior = 1.0;
	(*geo)->mater->reflectivity = 1.;
	return (1);
}

void				add_coeff_to_objet(t_geo *geo, t_color kd,t_color ks, double ior)
{
	
	/*geo->mater->kd = kd;
	geo->mater->ks = ks;
	geo->mater->ior = ior;*/
}

static int			setup_geo(t_geo **geo)
{
	*geo = malloc(sizeof(t_geo));
	if (!*geo)
		return (0);
	(*geo)->origin = vec3_new(0, 0, 0);
	if (!(*geo)->origin || !(setup_geo_mater(geo)))
	{
		free(*geo);
		return (0);
	}
	(*geo)->rotation = NULL;
	(*geo)->type = 0;
	(*geo)->curr = NULL;
	(*geo)->is_hit = NULL;
	(*geo)->tex = NULL;
	(*geo)->next = NULL;
	return (1);
}

int					malloc_geo(void **type, int size, int geo_id, t_geo **geo)
{
	if (!setup_geo(geo))
		return (0);
	*type = malloc(size);
	if (!*type)
		return (0);
	(*geo)->curr = *type;
	(*geo)->type = geo_id;
	(*geo)->is_hit = g_get_obj_collider(geo_id);
	return (1);
}

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
			tmp->neg = neg0;
			return (1);
		}
	}
	return (0);
}
