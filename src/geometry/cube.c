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

void				create_axis(t_geo *geo)
{
	t_cube			*cube;
	t_vec3			dir1;
	t_vec3			dir2;
	t_vec3			dir3;

	cube = (t_cube*)geo->curr;
	dir1 = cube->direction1;
	vec3_normalize(&dir1);
	if (dir1.z != 0.0)
	{
		dir2 = vec3_stack(1.0, 1.0, - (dir1.x + dir1.y) / dir1.z);
		dir3 = vec3_cross_prod_stack(dir1, dir2);
	}
	else if (dir1.y != 0.0)
	{
		dir2 = vec3_stack(1.0, -dir1.x / dir1.y, 0.0);
		dir3 = vec3_cross_prod_stack(dir1, dir2);
	}
	else
	{
		dir2 = vec3_stack(0.0, 1.0, 0.0); 
		dir3 = vec3_stack(0.0, 0.0, 1.0); 
	}
	vec3_normalize(&dir2);
	vec3_normalize(&dir3);
	cube->direction2 = dir2;
	cube->direction3 = dir3;
//	puts("DIRECS\n");
	cube->direction1 = dir1;
	/*vec3_print(cube->direction1);
	vec3_print(cube->direction2);
	vec3_print(cube->direction3);*/
}

t_geo				*new_cube(t_vec3 *position, t_vec3 dir1, double size)
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


t_vec3				cube_norm(t_geo *geo, t_hp hp)
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
	if (fabs(vec3_dot(diff, cube->direction2)) > max)
	{
		max = fabs(vec3_dot(diff, cube->direction2)); 
		if (vec3_dot(diff, cube->direction2) > 0)
			normal = cube->direction2;
		else
			normal = vec3_mult_stack(cube->direction2, -1.0);
	}
	if (fabs(vec3_dot(diff, cube->direction3)) > max)
	{
		if (vec3_dot(diff, cube->direction3) > 0)
			normal = cube->direction2;
		else
			normal = vec3_mult_stack(cube->direction3, -1.0);
	}
	return (normal);
}

static int					belong_to_inter_of_cube(t_geo *geo, double t, t_inter *i)
{
	t_cube	*cube;

	cube = (t_cube*)geo->curr;
	if (t < i[0].t_start || t > i[0].t_end || t < i[1].t_start || t > i[1].t_end || t < i[2].t_start || t > i[2].t_end)
		return (0);
	return (1);	
}

static double				max_3_interval(t_geo *geo, t_inter *i)
{
	double t;

	t = max(i[0].t_start, max(i[1].t_start, i[2].t_start));
	if (t > 0 && belong_to_inter_of_cube(geo, t, i))
		return (t);
	return (-1.0);
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

	
	/*limit[0].t_start = min((cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction1)) / vec3_dot(r.direction, cube->direction1), (-cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction1)) / vec3_dot(r.direction, cube->direction1));
	limit[0].t_end = max((cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction1)) / vec3_dot(r.direction, cube->direction1), (-cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction1)) / vec3_dot(r.direction, cube->direction1));
	limit[1].t_start = min((cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction2)) / vec3_dot(r.direction, cube->direction2), (-cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction2)) / vec3_dot(r.direction, cube->direction2));
	limit[1].t_end = max((cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction2)) / vec3_dot(r.direction, cube->direction2), (-cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction2)) / vec3_dot(r.direction, cube->direction2));
	limit[2].t_start = min((cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction3)) / vec3_dot(r.direction, cube->direction3), (-cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction3)) / vec3_dot(r.direction, cube->direction3));
	limit[2].t_end = max((cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction3)) / vec3_dot(r.direction, cube->direction3), (-cube->size - vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction3)) / vec3_dot(r.direction, cube->direction3));*/	
	/*printf("T_START %f T_END %f \n",limit[0].t_start, limit[0].t_end);
	printf("T_START %f T_END %f \n",limit[1].t_start, limit[1].t_end);	
	printf("T_START %f T_END %f \n",limit[2].t_start, limit[2].t_end);*/
	/*vec3_print(vec3_sub_stack(*geo->origin, r.origin));
	vec3_print(cube->direction3);
	printf("VALEUR %f %f \n",cube->size, 1.0);*/
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
			//puts("HIT NOON\n");
			sol.t = -1;
			return (sol);
		}
		//puts("HIT\n");
	}
	return (sol);
}
