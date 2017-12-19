/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/14 14:00:54 by chaueur          ###   ########.fr       */
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
		dir2 = vec3_stack(1.0, 1.0, - (dir1.x + dir1.y) / dir1.z);
	else if (dir1.y != 0.0)
		dir2 = vec3_stack(1.0, -dir1.x / dir1.y, 0.0);
	else
	{
		dir2 = vec3_stack(0.0, 1.0, 0.0); 
		dir3 = vec3_stack(0.0, 0.0, 1.0); 
	}
	dir3 = vec3_cross_prod_stack(dir1, dir2);
	vec3_normalize(&dir2);
	vec3_normalize(&dir3);
	cube->direction2 = dir2;
	cube->direction3 = dir3;
}

t_geo				*new_cube(t_vec3 *position, t_vec3 dir1, \
	double size)
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
	//printf("T %f\n", t);
	if (t < i[0].t_start || t > i[0].t_end || t < i[1].t_start || t > i[1].t_end || t < i[2].t_start)
	{
			//puts("ORNELLA");
			return (0);
	}
	/*if (t < i[0].t_start)
		puts("A1");
	if (t > i[0].t_end)
		puts("A2");
	if (t < i[1].t_start)
		puts("A3");
	if (t > i[1].t_end)
		puts("A4");
	if (t < i[2].t_start)
		puts("A5");
	if (t > i[2].t_end)
		puts("A6");*/
	//puts("Valide");
	return (1);	
}

static double				max_3_interval(t_geo *geo, t_ray r , t_inter *i)
{
	double t;

	t = max(i[0].t_start, max(i[1].t_start, i[2].t_start));
	printf("T %f\n", t);	
	if (t > 0 && belong_to_inter_of_cube(geo, t, i))
		return (t);
	return (-1.0);
}

double				solutions_cube(t_geo *geo, t_ray r)
{
	t_cube			*cube;
	t_inter			limit[3];

	cube = (t_cube*)geo->curr;
	printf("R DIRECTION [%f, %f, %f]\n", r.direction.x, r.direction.y, r.direction.z);

	limit[0].t_start = 0.0;
	limit[0].t_end = 0.0;
	limit[1].t_start = 0.0; 
	limit[1].t_end = 0.0;
	limit[2].t_start = 0.0;
	limit[2].t_end = 0.0;

	limit[0].t_start = min((cube->position.x - r.origin.x - cube->size) / r.direction.x, (cube->position.x - r.origin.x + cube->size) / r.direction.x);
	limit[0].t_end = max((cube->position.x - r.origin.x - cube->size) / r.direction.x, (cube->position.x - r.origin.x + cube->size) / r.direction.x);;
	limit[1].t_start = min((cube->position.y - r.origin.y - cube->size) / r.direction.y,(cube->position.y - r.origin.y + cube->size) / r.direction.y); 
	limit[1].t_end = max((cube->position.y - r.origin.y - cube->size) / r.direction.y,(cube->position.y - r.origin.y + cube->size) / r.direction.y);
	limit[2].t_start = min((cube->position.z - r.origin.z - cube->size) / r.direction.z, (2 * cube->position.z - r.origin.z + cube->size) / r.direction.z);
	limit[2].t_end = max((cube->position.z - r.origin.z - cube->size) / r.direction.z, (2 * cube->position.z - r.origin.z + cube->size) / r.direction.z);
	printf("Valeur 1 %f - %f SIZE %f\n", (cube->position.z - r.origin.z)/ r.direction.z - (cube->size / r.direction.z), (2 * cube->position.z - r.origin.z) / r.direction.z + (cube->size / r.direction.z), cube->size);	
	printf("T_START %f T_END %f \n",limit[0].t_start, limit[0].t_end);
	printf("T_START %f T_END %f \n",limit[1].t_start, limit[1].t_end);	
	printf("T_START %f T_END %f \n",limit[2].t_start, limit[2].t_end);
	return (max_3_interval(geo, r, limit));
}

t_hp				hit_cube(t_geo *geo, t_ray r)
{
	t_hp			sol;
	double			t;

	sol.t = -1;
	t = solutions_cube(geo, r);
	//printf("T %f\n", t);
	if (t > 0)
	{
		sol.t = t;
		sol.p = point_at_parameter(sol.t, r);
		sol.normal = cube_norm(geo, sol);
	}
	return (sol);
}
