/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ref.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 12:12:35 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/05 17:04:13 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ray.h"
#include "light.h"
#include "pthread.h"
#include "rt.h"
#include "utils.h"
#include "geo.h"

static void			add_epsilon(t_ray *r, t_vec3 normal)
{
	float			eps;

	eps = 0.1;
	normal = vec3_normalize_stack(normal);
	if (vec3_dot(r->direction, normal) < 0)
		eps = -eps;
	r->origin = vec3_add_stack(r->origin, vec3_mult_stack(normal, eps));
}

t_ray				reflect_ray(t_ray r, t_hp hp)
{
	t_ray			r_refl;
	t_vec3			normal;
	t_vec3			i;
	t_vec3			refl;
	double			len;

	normal = hp.normal;
	i = r.direction;
	i = vec3_normalize_stack(i);
	normal = vec3_normalize_stack(normal);
	len = vec3_dot(i, normal);
	refl = vec3_add_mult_stack(i, normal, -2 * len);
	r_refl = init_ray(hp.p, refl, 3, r.ior);
	add_epsilon(&r_refl, normal);
	return (r_refl);
}

static int			value_c2(double n, double *c1, double *c2, t_vec3 *normal)
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

t_ray				refract_ray(t_geo *geo, t_ray r, t_hp hp) 
{
	t_ray			r_refr;
	t_vec3			t;
	double			ior_2;
	double			c1;
	double			c2;

	c2 = 0.0;
	ior_2 = find_ior(geo, r, hp);
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
	r_refr = init_ray(hp.p, t, 3, ior_2);
	add_epsilon(&r_refr, hp.normal);
	return (r_refr);
}
