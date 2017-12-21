/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:54:34 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/21 16:33:57 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"


t_geo					*new_paraboloid(t_vec3 *position, double a, double b)
{
	t_paraboloid	*pb;
	t_geo			*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&pb), sizeof(t_paraboloid), 6, &geo))
		return (0);
	geo->origin = position;
	pb->facta = a;
	pb->factb = b;
	pb->height = 1.0;
	return (geo);
}

int					belong_to_paraboloid(t_geo *geo, t_vec3 pos)
{
	t_paraboloid	*para;
	double			res;

	para = (t_paraboloid*)geo->curr;
	res = pow((pos.x / para->facta), 2) - pow((pos.y / para->factb), 2) - \
		(pos.z / para->height);
	if (res == 0.0)
		return (1);
	return (0);
}

t_vec3				para_norm(t_geo *geo, t_vec3 hp)
{
	t_paraboloid 	*para;
	t_vec3			normal;

	para = (t_paraboloid*)geo;
	normal = vec3_stack(2 * hp.x / pow(para->facta, 2), -2 * hp.y / \
			pow(para->factb, 2), -1 / para->height);
	normal = vec3_normalize_stack(normal);
	return (normal);
}

t_hp				hit_paraboloid(t_geo *geo, t_ray *r)
{
	t_paraboloid	*para;
	t_hp			hp;
	double			abcd[4];

	para = (t_paraboloid *)geo->curr;
	hp.t = -1;
	if (para->facta == 0 || para->factb == 0 || para->height == 0)
		return (hp);
	abcd[0] = pow((r->direction.x / para->facta), 2) - \
		pow((r->direction.y / para->factb), 2);
	abcd[1] = (2 * r->origin.x * r->direction.x / pow(para->facta, 2)) - \
		(2 * r->origin.y * r->direction.y / pow(para->factb, 2)) - \
		(r->direction.z / para->height);
	abcd[2] = pow((r->origin.x / para->facta), 2) - \
		pow((r->origin.y / para->factb), 2) - (r->origin.z / para->height);
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] >= 0)
	{
		hp.t = positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
				(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
		hp.p = point_at_parameter(hp.t, r);
		hp.normal = para_norm(geo, hp.p);
	}
	return (hp);
}
