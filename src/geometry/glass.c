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

t_geo				*new_glass(t_vec3 *position, t_vec3 direction, \
	double height)
{
	t_glass			*glass;
	t_geo			*geo;

	/*geo = NULL;
	if (!malloc_geo((void **)(&glass), sizeof(t_glass), \
	8, &geo))
		return (0);
	geo->origin = position;
	glass->under = (t_cone*) new_cone(position, direction, 20);
	glass->basis = (t_sphere*) new_sphere(position, 0.3);
	glass->high = (t_cylinder*) new_cylinder(position, direction, 0.3);
	glass->direction = direction;
	glass->height = height;*/
	return (geo);
}

int					belong_to_glass(t_geo *geo, t_vec3 pos)
{
	t_glass			*glass;
	t_cone			*under;
	t_sphere		*basis;
	t_cylinder		*high;


	/*glass = (t_glass*)geo->curr;
	under = glass->under;
	basis = glass->basis;
	high = glass->high;
	if (belong_to_cone((t_geo*)under, pos) && belong_to_sphere(\
	(t_geo *)basis,pos) && belong_to_cylinder((t_geo *)high,pos))
		return (1);*/
	return (0);
}

/*t_vec3				cube_norm(t_geo *geo, t_hp hp)
{
	t_cube			*cube;
	t_vec3			diff;
	t_vec3			normal;
	double			max;

	cube = (t_cube*)geo->curr;
	diff = vec3_sub_stack(hp.p, *geo->origin);
	vec3_normalize(&cube->direction1);
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
	//printf("T %f\n", t);
	if (t < i[0].t_start || t > i[0].t_end || t < i[1].t_start || t > i[1].t_end || t < i[2].t_start || t > i[2].t_end)
	{
			//puts("ORNELLA");
			return (0);
	}
	return (1);	
}

static double				max_3_interval(t_geo *geo, t_inter *i)
{
	double t;

	t = max(i[0].t_start, max(i[1].t_start, i[2].t_start));
	//printf("T %f\n", t);	
	if (t > 0 && belong_to_inter_of_cube(geo, t, i))
		return (t);
	return (-1.0);
}*/

/*double				solutions_cube(t_geo *geo, t_ray r)
{
	t_cube			*cube;
	t_inter			limit[3];

	cube = (t_cube*)geo->curr;
	printf("R DIRECTION [%f, %f, %f]\n", r.direction.x, r.direction.y, r.direction.z);
	printf("R POSITION [%f, %f, %f]\n", geo->origin->x, geo->origin->y, geo->origin->z);
	limit[0].t_start = 0.0;
	limit[0].t_end = 0.0;
	limit[1].t_start = 0.0; 
	limit[1].t_end = 0.0;
	limit[2].t_start = 0.0;
	limit[2].t_end = 0.0;

	limit[0].t_start = min((geo->origin->x - r.origin.x - cube->size) / r.direction.x, (geo->origin->x - r.origin.x + cube->size) / r.direction.x);
	limit[0].t_end = max((geo->origin->x - r.origin.x - cube->size) / r.direction.x, (geo->origin->x - r.origin.x + cube->size) / r.direction.x);
	limit[1].t_start = min((geo->origin->y - r.origin.y - cube->size) / r.direction.y,(geo->origin->y - r.origin.y + cube->size) / r.direction.y); 
	limit[1].t_end = max((geo->origin->y - r.origin.y - cube->size) / r.direction.y,(geo->origin->y - r.origin.y + cube->size) / r.direction.y);
	limit[2].t_start = min((geo->origin->z - r.origin.z - cube->size) / r.direction.z, (geo->origin->z - r.origin.z + cube->size) / r.direction.z);
	limit[2].t_end = max((geo->origin->z - r.origin.z - cube->size) / r.direction.z, (geo->origin->z - r.origin.z + cube->size) / r.direction.z);
	printf("Valeur 1 %f - %f SIZE %f\n", (geo->origin->z - r.origin.z)/ r.direction.z - (cube->size / r.direction.z), (geo->origin->z - r.origin.z) / r.direction.z + (cube->size / r.direction.z), cube->size);
	limit[0].t_start = min((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction1)) / vec3_dot(r.direction, cube->direction1), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction1)) / vec3_dot(r.direction, cube->direction1));
	limit[0].t_end = max((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction1)) / vec3_dot(r.direction, cube->direction1), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction1)) / vec3_dot(r.direction, cube->direction1));
	limit[1].t_start = min((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction2)) / vec3_dot(r.direction, cube->direction2), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction2)) / vec3_dot(r.direction, cube->direction2));
	limit[1].t_end = max((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction2)) / vec3_dot(r.direction, cube->direction2), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction2)) / vec3_dot(r.direction, cube->direction2));
	limit[2].t_start = min((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction3)) / vec3_dot(r.direction, cube->direction3), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction3)) / vec3_dot(r.direction, cube->direction3));
	limit[2].t_end = max((cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction3)) / vec3_dot(r.direction, cube->direction3), (-cube->size + vec3_dot(vec3_sub_stack(*geo->origin, r.origin), cube->direction3)) / vec3_dot(r.direction, cube->direction3));

	printf("T_START %f T_END %f \n",limit[0].t_start, limit[0].t_end);
	printf("T_START %f T_END %f \n",limit[1].t_start, limit[1].t_end);	
	printf("T_START %f T_END %f \n",limit[2].t_start, limit[2].t_end);
	return (max_3_interval(geo, limit));
}*/

t_hp				hit_glass(t_geo *geo, t_ray r)
{
	t_hp			sol;
	double			x;

	sol.t = -1;
	x = solutions_cube(geo, r);
	//printf("T %f\n", t);
	if (x > 0)
	{
		sol.t = x;
		sol.p = point_at_parameter(sol.t, r);
		sol.normal = cube_norm(geo, sol);
	}
	return (sol);
}
