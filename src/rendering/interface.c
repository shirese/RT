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
		return (belong_to_pipe_2(g, pos));
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
	r_new = init_ray(r_new.origin, r.direction, 1, r.ior);
	r_new.color = r.color;
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
	r_refl = init_ray(hp.p, refl, 1, r.ior);
	r_refl = add_epsilon(r_refl, normal);
	return (r_refl);
}

static int				value_c2(double n, double *c1, double *c2, t_vec3 *normal)
{
	if (*c1 < 0)
		*c1 = -*c1;
	else
		*normal = vec3_mult_stack(*normal, -1);
	if (1 - (pow(n, 2) * (1 - pow(*c1, 2))) >= 0)
		*c2 = sqrt(1 - (pow(n, 2) * (1 - pow(*c1, 2))));
	else
		return (-1);
	return (1);
}

t_ray 				refract_ray(t_geo *geo, t_ray r, t_hp hp) 
{ 
	t_ray	r_refr;
	t_vec3 t;
	double ior_2;
	double c1;
	double c2;

	c2 = 0.0;
	ior_2 = ior_of_refraction(geo, r, hp);
	hp.normal = vec3_normalize_stack(hp.normal);
	c1 = clamp(vec3_dot(vec3_normalize_stack(r.direction), hp.normal), -1, 1);
	if (value_c2((r.ior / ior_2), &c1, &c2, &(hp.normal)) == - 1)
	{
		r_refr.type = 0;
		return (r_refr);
	}
	t = vec3_mult_stack(vec3_normalize_stack(r.direction), (r.ior / ior_2));
	t = vec3_add_stack(vec3_mult_stack(hp.normal, (r.ior / ior_2) * c1 - c2), t);
	t = vec3_normalize_stack(t);
	r_refr = init_ray(hp.p, t, 1, ior_2);
	r_refr = add_epsilon(r_refr, hp.normal);
	return (r_refr);
}
