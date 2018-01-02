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

t_geo					*new_cube(t_vec3 *position, t_vec3 dir1, double size)
{
	t_cube			*cube;
	t_geo			*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&cube), sizeof(t_cube), \
	7, &geo))
		return (0);
	geo->origin = position;
	cube->direction1 = dir1;
	cube->size = size;
	return (geo);
}

void					create_axis(t_geo *geo)
{
	t_cube			*cube;
	t_vec3			dir1;

	cube = (t_cube*)geo->curr;
	vec3_normalize(&cube->direction1);
	dir1 = cube->direction1;
	if (dir1.z != 0.0)
	{
		cube->direction2 = vec3_stack(1.0, 1.0, -\
			(dir1.x + dir1.y) / dir1.z);
		cube->direction3 = vec3_cross_prod_stack(dir1, \
			cube->direction2);
	}
	else if (dir1.y != 0.0)
	{
		cube->direction2 = vec3_stack(1.0, -dir1.x / dir1.y, 0.0);
		cube->direction3 = vec3_cross_prod_stack(dir1, cube->direction2);
	}
	else
	{
		cube->direction2 = vec3_stack(0.0, 1.0, 0.0);
		cube->direction3 = vec3_stack(0.0, 0.0, 1.0);
	}
	vec3_normalize(&cube->direction2);
	vec3_normalize(&cube->direction3);
}

static void				cube_norm2(t_geo *geo, t_vec3 diff, t_vec3 *normal)
{
	t_cube			*cube;
	double			max;

	cube = NULL;
	max = fabs(vec3_dot(diff, cube->direction1));
	cube = (t_cube*)geo->curr;
	if (fabs(vec3_dot(diff, cube->direction2)) > max)
	{
		max = fabs(vec3_dot(diff, cube->direction2));
		if (vec3_dot(diff, cube->direction2) > 0)
			*normal = cube->direction2;
		else
			*normal = vec3_mult_stack(cube->direction2, -1.0);
	}
	if (fabs(vec3_dot(diff, cube->direction3)) > max)
	{
		if (vec3_dot(diff, cube->direction3) > 0)
			*normal = cube->direction3;
		else
			*normal = vec3_mult_stack(cube->direction3, -1.0);
	}
}

t_vec3					cube_norm(t_geo *geo, t_hp hp)
{
	t_cube			*cube;
	t_vec3			diff;
	t_vec3			normal;
	double			max;

	cube = (t_cube*)geo->curr;
	diff = vec3_sub_stack(hp.p, *geo->origin);
	max = fabs(vec3_dot(diff, cube->direction1));
	if (vec3_dot(diff, cube->direction1) > 0)
		normal = cube->direction1;
	else
		normal = vec3_mult_stack(cube->direction1, -1.0);
	cube_norm2(geo, diff, &normal);
	return (normal);
}

int						belong_to_inter_of_cube(t_geo *geo, \
double t, t_inter *i)
{
	t_cube	*cube;

	cube = (t_cube*)geo->curr;
	if (t < i[0].t_start || t > i[0].t_end || t < i[1].t_start || \
	t > i[1].t_end || t < i[2].t_start || t > i[2].t_end)
		return (0);
	return (1);
}
