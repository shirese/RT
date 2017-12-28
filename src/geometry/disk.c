/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:51:32 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/15 15:03:25 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

t_geo				*new_disk(t_vec3 *position, t_vec3 normal, double radius)
{
	t_disk			*d;
	t_geo			*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&d), sizeof(t_disk), 5, &geo))
		return (0);
	geo->origin = position;
	d->normal = normal;
	d->radius = radius;
	return (geo);
}

t_vec3				disk_norm(t_geo *geo)
{
	t_disk			*d;

	d = (t_disk*)geo->curr;
	return (d->normal);
}

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

void				fill_solution_disk(t_geo *geo, t_ray r, \
double *expr, t_hp *sol)
{
	t_disk *d;

	d = (t_disk *)geo->curr;
	if (expr[0] >= 0)
	{
		expr[1] = pow(r.origin.x + expr[0] * r.direction.x - \
		(*geo->origin).x, 2) + pow(r.origin.y + expr[0] * \
		r.direction.y - (*geo->origin).y, 2) + \
		pow(r.origin.z + expr[0] * r.direction.z - \
		(*geo->origin).z, 2) - pow(d->radius, 2);
		if (expr[1] <= 0)
		{
			sol->t = expr[0];
			sol->p = point_at_parameter(sol->t, r);
			sol->normal = d->normal;	
		}
	}
	if (is_cut(geo) && !belong_after_cut(geo, sol->p))
			sol->t = -1;
}

t_hp				hit_disk(t_geo *geo, t_ray r)
{
	double			expr[2];
	t_disk			*d;
	t_hp			sol;

	d = (t_disk *)geo->curr;
	sol.t = -1;
	vec3_normalize(&(d->normal));
	expr[0] = vec3_dot(vec3_sub_stack(*geo->origin, r.origin), d->normal);
	expr[0] = expr[0] / vec3_dot(d->normal, r.direction);
	fill_solution_disk(geo, r, expr, &sol);
	return (sol);
}
