/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/14 12:29:43 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

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

t_vec3				cylinder_norm(t_geo *geo, t_hp hp)
{
	t_cylinder 		*cyl;
	t_vec3			normal;
	t_vec3			tmp;
	t_vec3			project;
	float			dot;

	cyl = (t_cylinder *)geo;
	tmp = vec3_sub_stack(hp.p, *geo->origin);
	dot = vec3_dot(tmp, cyl->axis);
	project = vec3_mult_stack(cyl->axis, dot);
	normal = vec3_sub_stack(tmp, project);
	vec3_normalize(&normal);
	return (normal);
}

t_hp				hit_cylinder(t_geo *geo, t_ray r)
{
	t_cylinder		*cyl;
	t_hp			hp_1;
	t_hp			hp_2;
	t_vec3			x;
	double			abcd[4];
	double			dot[2];

	hp_1.t = -1;
	cyl = (t_cylinder *)geo->curr;
	x = vec3_sub_stack(r.origin, *geo->origin);
	vec3_normalize(&cyl->axis);
	dot[0] = vec3_dot(r.direction, cyl->axis);
	dot[1] = vec3_dot(x, cyl->axis);
	abcd[0] = vec3_dot(r.direction, r.direction) - dot[0] * dot[0];
	abcd[1] = 2 * (vec3_dot(r.direction, x) - dot[0] * dot[1]);
	abcd[2] = vec3_dot(x, x) - dot[1] * dot[1] - cyl->radius * cyl->radius;
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] > 0)
	{
		hp_1.t = positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
			(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
		hp_1.p = point_at_parameter(hp_1.t, r);
		hp_1.normal = norm_cut(geo, hp_1);
		
		hp_2.t = non_positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
			(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
		hp_2.p = point_at_parameter(hp_2.t, r);
		hp_2.normal = norm_cut(geo, hp_2);
		return (hit_and_cut(geo, hp_1, hp_2, r));
	}
	return (hp_1);
}
