/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 10:35:24 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/22 16:31:08 by chaueur          ###   ########.fr       */
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

static t_hp			hit_ortho(t_ray *r, t_plane *p, t_vec3 min)
{
	t_hp			hp;

	hp.t = -1;
	vec3_normalize(&p->normal);
	if (vec3_dot(min, p->normal) == 0.0)
	{
		hp.p = vec3_stack(r->origin.x, r->origin.y, r->origin.z);
		hp.t = vec3_norm(vec3_sub_stack(r->origin, hp.p));
		hp.normal = p->normal;
	}
	return (hp);
}

t_hp				hit_plane(t_geo *geo, t_ray *r)
{
	t_hp			sol;
	t_plane			*p;
	double			dot[2];

	sol.t = -1;
	p = (t_plane*)geo->curr;
	dot[0] = vec3_dot(p->normal, vec3_sub_stack(*geo->origin, r->origin));
	if ((dot[1] = vec3_dot(p->normal, r->dir)) == 0.0)
		return (hit_ortho(r, p, vec3_sub_stack(*geo->origin, r->origin)));
	else if (fabs(vec3_dot(p->normal, r->dir)) > 1e-6)
	{
		dot[0] /= vec3_dot(p->normal, r->dir);
		if (dot[0] > 0.0)
		{
			sol.p = vec3_stack(r->origin.x + dot[0] * r->dir.x, r->origin.y \
			+ dot[0] * r->dir.y, r->origin.z + dot[0] * r->dir.z);
			sol.t = vec3_norm(vec3_sub_stack(r->origin, sol.p));
			sol.normal = p->normal;
			if (is_cut(geo) && !belong_after_cut(geo, sol))
				sol.t = -1;
			if (is_geo_dug(geo))
				return (is_touched_by_neg(geo, r, sol));
		}
	}
	return (sol);
}
