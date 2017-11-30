/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:04:54 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/08 17:36:37 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ray.h"
#include "light.h"
#include "pthread.h"
#include "rt.h"
#include "utils.h"
#include "geo.h"

int 				belong_to(t_geo *g, t_vec3 pos)
{
	if (g->type == 1)
		return (belong_to_plane(g, pos));
	else if (g->type == 2)
		return (belong_to_cone(g, pos));
	else if (g->type == 3)
		return (belong_to_cylinder(g, pos));
	else if (g->type == 4)
		return (belong_to_sphere(g, pos));
	else if (g->type == 5)
		return (belong_to_disk(g, pos));
	else if (g->type == 6)
		return (belong_to_pipe(g, pos));
	return (0);
}

t_ray				add_epsilon(t_ray r, t_vec3 normal)
{
	t_ray	r_new;
	float	eps;

	eps = 0.1;
	normal = vec3_normalize_stack(normal);
	if (vec3_dot(r.direction, normal) > 0)
		r_new.origin = vec3_add_mult_stack(r.origin, normal, eps);
	else if (vec3_dot(r.direction, normal) < 0)
		r_new.origin = vec3_add_mult_stack(r.origin, normal, -eps);
	r_new.type = 1;
	r_new.direction = r.direction;
	r_new.point_at_parameter = r.point_at_parameter;
	r_new.color = r.color;
	r_new.ior = r.ior;
	return (r_new);
}

t_ray				reflect_ray(t_ray r, t_hp hp)
{
	t_ray		r_refl;
	t_vec3 		normal;
	t_vec3 		i;
	t_vec3 		refl;
	double 		len;

	normal = hp.normal;
	i = r.direction;
	i = vec3_normalize_stack(i);
	normal = vec3_normalize_stack(normal);
	len = vec3_dot(i, normal);
	refl = vec3_add_mult_stack(i, normal, -2 * len);
	r_refl.type = 1;
	r_refl.origin = hp.p;
	r_refl.direction = refl;
	r_refl.point_at_parameter = vec3_stack(0.0, 0.0, 0.0);
	r_refl.color = color_new_stack(0.0, 0.0, 0.0, 0.0);
	r_refl.ior = r.ior;
	/*while (belong_to(g, r_refl.origin))
	{
		r_refl = add_epsilon(r_refl, normal);
		puts("fred");
	}*/
	r_refl = add_epsilon(r_refl, normal);
	return (r_refl);
}

t_ray 				refract_ray(t_geo *geo, t_ray r, t_hp hp) 
{ 
	t_ray	r_refr;
	t_vec3 i;
	t_vec3 t;
	t_vec3 t2;
	double ior_1;
	double ior_2;
	double c1;
	double c2;
	double n;

	c2 = 0.0;
	ior_1 = r.ior;
	ior_2 = ior_of_refraction(geo, r, hp);
	i = r.direction;
	i = vec3_normalize_stack(i);
	hp.normal = vec3_normalize_stack(hp.normal);
	c1 = clamp(vec3_dot(i, hp.normal), -1, 1);
	n = (ior_1 / ior_2);
	if (1 - (pow(n, 2) * (1 - pow(c1, 2))) >= 0)
		c2 = sqrt(1 - (pow(n, 2) * (1 - pow(c1, 2))));
	t = vec3_mult_stack(i, n);
	t2 = vec3_mult_stack(hp.normal, n * c1 - c2);
	t = vec3_add_stack(t2, t);
	t = vec3_normalize_stack(t);
	r_refr.type = 1;
	r_refr.origin = hp.p;
	r_refr.direction = t;
	r_refr.point_at_parameter = vec3_stack(0.0, 0.0, 0.0);
	r_refr.color = color_new_stack(0.0, 0.0, 0.0, 0.0);
	r_refr.ior = ior_2;
	r_refr = add_epsilon(r_refr, hp.normal);
	return (r_refr);
}
