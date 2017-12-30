/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/28 15:49:03 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

static double				max_3_interval(t_geo *geo, t_inter *i)
{
	double t;

	t = max(i[0].t_start, max(i[1].t_start, i[2].t_start));
	if (t > 0 && belong_to_inter_of_cube(geo, t, i))
		return (t);
	return (-1.0);
}

int					belong_to_cube(t_geo *geo, t_vec3 pos)
{
	t_cube			*cube;
	t_vec3			diff;
	double			len;

	cube = (t_cube*)geo->curr;
	diff = vec3_sub_stack(pos, *geo->origin);
	len = vec3_dot(diff, cube->direction1);
	if (fabs(len) <= cube->size)
		return (1);
	return (0);
}

double				cube_solutions(t_geo *geo, t_ray *r)
{
	t_cube			*cube;
	t_inter			limit[3];

	cube = (t_cube*)geo->curr;
	limit[0].t_start = min((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction1)) / vec3_dot(r->dir, cube->direction1), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction1)) / vec3_dot(r->dir, cube->direction1));
	limit[0].t_end = max((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction1)) / vec3_dot(r->dir, cube->direction1), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction1)) / vec3_dot(r->dir, cube->direction1));
	limit[1].t_start = min((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction2)) / vec3_dot(r->dir, cube->direction2), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction2)) / vec3_dot(r->dir, cube->direction2));
	limit[1].t_end = max((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction2)) / vec3_dot(r->dir, cube->direction2), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction2)) / vec3_dot(r->dir, cube->direction2));
	limit[2].t_start = min((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction3)) / vec3_dot(r->dir, cube->direction3), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction3)) / vec3_dot(r->dir, cube->direction3));
	limit[2].t_end = max((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction3)) / vec3_dot(r->dir, cube->direction3), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r->origin), cube->direction3)) / vec3_dot(r->dir, cube->direction3));
	return (max_3_interval(geo, limit));
}

t_hp				hit_cube(t_geo *geo, t_ray *r)
{
	t_hp			sol;
	double			x;

	sol.t = -1;
	x = cube_solutions(geo, r);
	if (x > 0)
	{
		sol.t = x;
		sol.p = point_at_parameter(sol.t, r);
		sol.normal = cube_norm(geo, sol);
		if (is_cut(geo) && !belong_after_cut(geo, sol.p))
		{
			sol.t = -1;
			return (sol);
		}
	}
	return (sol);
}
