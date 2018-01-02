/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 10:35:24 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/02 14:14:10 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rt.h"

t_geo				*new_plane(t_vec3 *position, t_vec3 normal)
{
	t_plane		*plane;
	t_geo		*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&plane), sizeof(t_plane), 1, &geo))
		return (0);
	geo->origin = position;
	plane->normal = normal;
	return (geo);
}

t_vec3				plane_norm(t_geo *geo)
{
	t_plane *plane;

	plane = (t_plane*)geo->curr;
	return (plane->normal);
}

int					belong_to_plane(t_geo *geo, t_vec3 pos)
{
	t_plane			*plane;
	t_vec3			diff;

	plane = (t_plane*)geo->curr;
	diff = vec3_sub_stack(*geo->origin, pos);
	if (vec3_dot(diff, plane->normal) == 0.0)
		return (1);
	return (0);
}

t_hp				hit_plane(t_geo *geo, t_ray *r)
{
	t_hp			sol;
	t_plane			*p;
	double			dot;
	double			t;

	sol.t = -1;
	p = (t_plane*)geo->curr;
	dot = vec3_dot(vec3_normalize_stack(p->normal), r->dir);
	if (fabs(dot) > 1e-6)
	{
		t = vec3_dot(vec3_sub_stack(*geo->origin, r->origin), p->normal) / dot;
		if (t >= 0.0001)
		{
			sol.p = vec3_stack(r->origin.x + t * r->dir.x, r->origin.y \
			+ t * r->dir.y, r->origin.z + t * r->dir.z);
			sol.t = t;
			sol.normal = p->normal;
			if (is_cut(geo) && !belong_after_cut(geo, sol))
				sol.t = -1;
			if (is_geo_dug(geo))
				return (is_touched_by_neg(geo, r, sol));
		}
	}
	return (sol);
}
