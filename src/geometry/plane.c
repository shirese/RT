/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 10:35:24 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/19 12:19:29 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rtv1.h"

static t_hp			hit_ortho(t_ray r, t_plane *p, t_vec3 min)
{
	t_hp			hp;

	hp.t = -1;
	vec3_normalize(&p->normal);
	if (vec3_dot(min, p->normal) == 0.0)
	{
		hp.p = vec3_stack(r.origin.x, r.origin.y, r.origin.z);
		hp.t = vec3_norm(vec3_sub_stack(r.origin, hp.p));
		hp.normal = p->normal;
	}
	return (hp);
}

t_hp				hit_plane(t_geo *geo, t_ray r)
{
	t_hp			hp;
	t_vec3			min;
	t_plane			*p;
	double			dot[2];

	hp.t = -1;
	min = vec3_sub_stack(*geo->origin, r.origin);
	p = geo->curr;
	dot[0] = vec3_dot(p->normal, min);
	dot[1] = vec3_dot(p->normal, r.direction);
	if (dot[1] == 0.0)
		return (hit_ortho(r, p, min));
	else if (fabs(dot[1]) > 1e-6)
	{
		dot[0] /= dot[1];
		if (dot[0] > 0.0)
		{
			hp.p = vec3_stack(r.origin.x + dot[0] * \
			r.direction.x, r.origin.y + dot[0] * r.direction.y, \
			r.origin.z + dot[0] * r.direction.z);
			hp.t = vec3_norm(vec3_sub_stack(r.origin, hp.p));
			hp.normal = p->normal;
		}
	}
	return (hp);
}
