/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 16:25:37 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

t_geo				*new_cylinder(t_vec3 *position, t_vec3 axis, double radius)
{
	t_cylinder 	*cyl;
	t_geo		*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&cyl), sizeof(t_cylinder), 3, &geo))
		return (0);
	geo->origin = position;
	cyl->axis = axis;
	cyl->radius = radius;
	return (geo);
}

int					belong_to_cylinder(t_geo *geo, t_vec3 pos)
{
	t_cylinder		*cyl;
	t_vec3			diff;
	t_vec3			proj;
	t_vec3			dif;
	double			len;

	cyl = (t_cylinder*)geo->curr;
	diff = vec3_sub_stack(pos, *geo->origin);
	len = vec3_dot(diff, cyl->axis);
	proj = vec3_add_stack(*geo->origin, \
		vec3_mult_stack(cyl->axis, len));
	dif = vec3_sub_stack(proj, pos);
	if (vec3_norm(dif) <= cyl->radius)
		return (1);
	return (0);
}

t_vec3		cylinder_norm(t_geo *geo, t_vec3 hp)
{
	t_cylinder 		*cyl;
	t_vec3			normal;
	t_vec3			tmp;
	t_vec3			project;
	float			dot;

	cyl = (t_cylinder*)geo->curr;
	tmp = vec3_sub_stack(hp, *geo->origin);
	dot = vec3_dot(tmp, cyl->axis);
	project = vec3_mult_stack(cyl->axis, dot);
	normal = vec3_sub_stack(tmp, project);
	vec3_normalize(&normal);
	return (normal);
}

void				solutions_cylinder(t_geo *geo, t_ray r, t_hp *sol)
{
	t_cylinder		*cyl;
	t_vec3			x;
	double			dot[2];
	double			abcd[4];
	
	cyl = (t_cylinder *)geo->curr;
	x = vec3_sub_stack(r.origin, *geo->origin);
	vec3_normalize(&cyl->axis);
	dot[0] = vec3_dot(r.direction, cyl->axis);
	dot[1] = vec3_dot(x, cyl->axis);
	abcd[0] = vec3_dot(r.direction, r.direction) - dot[0] * dot[0];
	abcd[1] = 2 * (vec3_dot(r.direction, x) - dot[0] * dot[1]);
	abcd[2] = vec3_dot(x, x) - dot[1] * dot[1] - cyl->radius * cyl->radius;
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	sol[0].t = -1;
	sol[1].t = -1;
	if (abcd[3] > 0)
	{
		sol[0].t = positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
			(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
		sol[0].p = point_at_parameter(sol[0].t, r);
		sol[0].normal = cylinder_norm(geo, sol[0].p);
		sol[1].t = non_positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
			(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
		sol[1].p = point_at_parameter(sol[1].t, r);
		sol[1].normal = cylinder_norm(geo, sol[1].p);
	}
}

t_hp				hit_cylinder(t_geo *geo, t_ray r)
{
	t_hp			sol[2];

	solutions_cylinder(geo, r, sol);
	if (sol[0].t > 0)
	{
		if (is_geo_dug(geo))
			return (first_outside_neg(geo, r, sol));
		return (sol[0]);
	}
	return (sol[0]);
}
