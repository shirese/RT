/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/21 16:26:31 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

t_geo				*new_cylinder(t_vec3 *position, t_vec3 axis, \
	double radius)
{
	t_cylinder		*cyl;
	t_geo			*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&cyl), sizeof(t_cylinder), \
	3, &geo))
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
	if (vec3_norm(dif) <= cyl->radius && belong_after_cut(geo, pos))
		return (1);
	return (0);
}

t_vec3				cylinder_norm(t_geo *geo, t_hp hp)
{
	t_cylinder		*cyl;
	t_vec3			normal;
	t_vec3			tmp;
	t_vec3			project;
	float			dot;

	cyl = (t_cylinder *)geo->curr;
	tmp = vec3_sub_stack(hp.p, *geo->origin);
	dot = vec3_dot(tmp, cyl->axis);
	project = vec3_mult_stack(cyl->axis, dot);
	normal = vec3_sub_stack(tmp, project);
	vec3_normalize(&normal);
	return (normal);
}

void				cylinder_solutions(t_geo *geo, t_ray *r, t_hp *sol)
{
	t_cylinder		*cyl;
	t_vec3			x;
	double			dot[2];
	double			abcd[4];

	sol[0].t = -1;
	sol[1].t = -1;
	cyl = (t_cylinder *)geo->curr;
	x = vec3_sub_stack(r->origin, *geo->origin);
	dot[0] = vec3_dot(r->dir, cyl->axis);
	dot[1] = vec3_dot(x, cyl->axis);
	abcd[0] = vec3_dot(r->dir, r->dir) - dot[0] * dot[0];
	abcd[1] = 2 * (vec3_dot(r->dir, x) - dot[0] * dot[1]);
	abcd[2] = vec3_dot(x, x) - dot[1] * dot[1] - cyl->radius * cyl->radius;
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] > 0)
		solve_cylinder(geo, r, abcd, sol);
}

t_hp				hit_cylinder(t_geo *geo, t_ray *r)
{
	t_hp			sol[2];

	cylinder_solutions(geo, r, sol);
	if (sol[0].t > 0)
	{
		if (is_geo_dug(geo) && is_cut(geo))
			return (first_in_cut_out_neg(geo, r, sol));
		else if (is_geo_dug(geo))
			return (first_outside_neg(geo, r, sol));
		return (hit_and_cut(geo, sol[0], sol[1], r));
	}
	return (sol[0]);
}
