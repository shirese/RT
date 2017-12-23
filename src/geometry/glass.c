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
	t_geo			*cyl;
	t_geo			*cone;
	t_geo			*sphere;


	glass = (t_glass*)geo->curr;
	cyl = glass->cyl;
	cone = glass->cone;
	sphere = glass->sphere;
	if (belong_to_cone(cone, pos) || belong_to_sphere(sphere,pos)\
	 || belong_to_cylinder(cyl,pos))
		return (1);
	return (0);
}

t_vec3				glass_norm(t_geo *geo, t_hp hp)
{
	t_glass 	*glass;
	t_geo		*cyl;
	t_geo		*cone;
	t_geo		*sphere;

	glass = (t_glass*)geo->curr;
	cyl = glass->cyl;
	cone = glass->cone;
	sphere = glass->sphere;

	if (belong_to_cylinder(cyl, hp.p))
		return (normal_cut(cyl, hp));
	if (belong_to_cone(cone, hp.p))
		return (normal_cut(cyl, hp));
		
	if (belong_to_sphere(sphere, hp.p))
		return (sphere_norm(sphere, hp.p));
	return (vec3_stack(0.0, 0.0, 0.0));
}

t_hp				nearest_part(t_hp	*sols)
{	
	double	t;

	t = positive_smallest(sols[0].t, positive_smallest(sols[1].t, sols[2].t));
	if (t == sols[0].t)
		return (sols[0]);
	else if (t == sols[1].t)
		return (sols[1]);
	else
		return (sols[2]);	
}

t_hp				hit_glass(t_geo *geo, t_ray r)
{
	t_glass 	*glass;
	t_geo		*cyl;
	t_geo		*cone;
	t_geo		*sphere;
	t_hp		sols[3];

	glass = (t_glass*)geo->curr;
	cyl = glass->cyl;
	cone = glass->cone;
	sphere = glass->sphere;
	sols[0] = hit_cylinder(cyl, r);
	sols[1] = hit_cone(cone, r);
	sols[2] = hit_sphere(sphere, r);
	return (nearest_part(sols));
}
