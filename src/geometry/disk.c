/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:51:32 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/14 12:29:34 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int					belong_to_disk(t_geo *geo, t_vec3 pos)
{
	t_disk			*d;
	t_vec3			diff;
	double			len;

	d = (t_disk*)geo->curr;
	diff = vec3_sub_stack(*geo->origin, pos);
	len = vec3_dot(diff, d->normal);
	if (len == 0.0 && vec3_norm(diff) <= d->radius)
		return (1);
	return (0);
}

t_hp				hit_disk(t_geo *geo, t_ray r)
{
	double			expr[2];
	t_disk			*d;
	t_hp			hp;

	d = (t_disk *)geo->curr;
	hp.t = -1;
	vec3_normalize(&(d->normal));
	expr[0] = ((*geo->origin).x - r.origin.x) * d->normal.x + \
	((*geo->origin).y - r.origin.y) * d->normal.y + \
	((*geo->origin).z - r.origin.z) * d->normal.z;
	expr[0] = expr[0] / (d->normal.x * r.direction.x + d->normal.y * \
		r.direction.y + d->normal.z * r.direction.z);
	if (expr[0] >= 0)
		expr[1] = pow(r.origin.x + expr[0] * r.direction.x - \
		(*geo->origin).x, 2) + pow(r.origin.y + expr[0] * \
		r.direction.y - (*geo->origin).y, 2) + \
		pow(r.origin.z + expr[0] * r.direction.z - \
		(*geo->origin).z, 2) - pow(d->radius, 2);
	if (expr[1] <= 0)
	{
		hp.t = expr[0];
		hp.p = point_at_parameter(hp.t, r);
		hp.normal = d->normal;
	}
	return (hp);
}
