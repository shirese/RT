/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 11:45:04 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/18 15:39:44 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

t_hp					hit_disk(t_geo *geo, t_ray r)
{
	double				expr[2];
	t_disk				*d;
	t_hp				hp;

	d = (t_disk *)geo->curr;
    hp.t = -1;
    vec3_normalize(&(d->normal));
    vec3_normalize(&(r.direction));
    expr[0] = ((*geo->origin).x - r.origin.x) * d->normal.x + ((*geo->origin).y - r.origin.y) * d->normal.y + \
    ((*geo->origin).z - r.origin.z) * d->normal.z;
    expr[0] = expr[0] / (d->normal.x * r.direction.x + d->normal.y * r.direction.y + d->normal.z * r.direction.z);
    if (expr[0] >= 0)
        expr[1] = pow(r.origin.x + expr[0] * r.direction.x - (*geo->origin).x, 2) + pow(r.origin.y + expr[0] * r.direction.y - (*geo->origin).y, 2) + \
    pow(r.origin.z + expr[0] * r.direction.z - (*geo->origin).z, 2) - pow(d->radius, 2);
    if (expr[1] <= 0)
    {
        hp.t = expr[0];
       
        hp.p = point_at_parameter(hp.t, r);
        hp.normal = d->normal;
    }
	return (hp);
}
