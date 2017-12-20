/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 16:19:56 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/14 13:49:10 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

t_geo				*new_sphere(t_vec3 *position, double radius)
{
	t_sphere		*sphere;
	t_geo			*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&sphere), sizeof(t_sphere), 4, &geo))
		return (0);
	geo->origin = position;
	sphere->radius = radius;
	return (geo);
}

t_vec3				sphere_norm(t_geo *geo, t_vec3 pos)
{
	t_vec3			norm;

	norm = vec3_sub_stack(pos, *geo->origin);
	vec3_normalize(&norm);
	return (norm);
}

int					belong_to_sphere(t_geo *geo, t_vec3 pos)
{
	t_sphere		*sphere;
	t_vec3			diff;

	sphere = (t_sphere*)geo->curr;
	diff = vec3_sub_stack(*geo->origin, pos);
	if (vec3_norm(diff) <= sphere->radius)
		return (1);
	return (0);
}

void				solutions_sphere(t_geo *geo, t_ray r, t_hp *sol)
{
	t_sphere		*sphere;
	double			abcd[4];
	double			t[2];
	t_vec3			oc;

	sol[0].t = -1;
	sol[1].t = -1;
	sphere = (t_sphere *)geo->curr;
	oc = vec3_sub_stack(r.origin, *geo->origin);
	abcd[0] = vec3_dot(r.direction, r.direction);
	abcd[1] = 2.0 * vec3_dot(oc, r.direction);
	abcd[2] = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] > 0)
	{
		t[0] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
		t[1] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
		sol[0].t = positive_smallest(t[0], t[1]);
		sol[0].p = point_at_parameter(sol[0].t, r);
		sol[1].t = non_positive_smallest(t[0], t[1]);
		sol[1].p = point_at_parameter(sol[1].t, r);
		sol[0].normal = sphere_norm(geo, sol[0].p);
		sol[1].normal = sphere_norm(geo, sol[1].p);
	}
}

t_hp				hit_sphere(t_geo *geo, t_ray r)
{
	t_hp			sol[2];

	solutions_sphere(geo, r, sol);
	if (sol[0].t > 0)
	{
		if (is_cut(geo))
			return (hit_and_cut(geo, sol[0], sol[1], r));
		if (is_geo_dug(geo))
			return (first_outside_neg(geo, r, sol));
		return (sol[0]);
	}
	return (sol[0]);
}
