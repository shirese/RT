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

double 				ior_point(t_geo *geo, t_vec3 pos)
{
	t_geo *g;
	double res;

	res = 0;
	g = geo;
	while (g)
	{
		if (g->type == 1)
		{
			if (belong_to_plane(g, pos) == 1)
				return (g->mater->ior);
		}
		else if (g->type == 2)
		{
			if (belong_to_cone(g, pos) == 1)
				return (g->mater->ior);
		}
		else if ((res = ior_point2(g, pos)))
			return (res);
		g = g->next;	
	}
	return (1.0);
}

double 				ior_point2(t_geo *g, t_vec3 pos)
{
	if (g->type == 3)
	{
		if (belong_to_cylinder(g, pos) == 1)
			return (g->mater->ior);
	}
	else if (g->type == 4)
	{
		if (belong_to_sphere(g, pos) == 1)
				return (g->mater->ior);
	}
	else if (g->type == 5)
	{
		if (belong_to_disk(g, pos) == 1)
			return (g->mater->ior);
	}
	else if (g->type == 6)
	{
		if (belong_to_pipe_2(g, pos) == 1)
		{
			return (g->mater->ior);
		}
	}
	return (0.0);
}

double				ior_of_refraction(t_geo *geo, t_ray r, t_hp hp)
{
	t_geo	*g;
	t_vec3 diff;
	t_vec3 eps;
	t_vec3 i;
	double len;

	g = geo;
	diff = vec3_sub_stack(hp.p, r.origin);
	len = vec3_norm(diff);
	i = r.direction;
	i = vec3_normalize_stack(i);
	eps = vec3_add_mult_stack(r.origin, i, len + EPSILON);
	return (ior_point(geo, eps));
}

double		find_krefl(t_geo *geo, t_hp hp, t_ray r)
{
	if (geo->mater->kg.g == 1.0)
		return (1);
	else if (geo->mater->kg.b == 1.0)
		return (0);
	else if (geo->mater->kg.a == 1.0)
		return (coeff_fresnel(r, hp, geo));
	return (0);
}

double		coeff_fresnel(t_ray r, t_hp hp, t_geo *geo)
{
	double cosi;
	double sint;
	double cost;
	double rs;
	double n;

	n = ior_of_refraction(geo, r, hp);
	r.direction = vec3_normalize_stack(r.direction);
	cosi = clamp(vec3_dot(r.direction, vec3_normalize_stack(hp.normal)), -1, 1);
	sint = (r.ior / n) * sqrt(max(0, 1 - pow(cosi, 2)));
	if (sint >= 1.0)
		return (1);
	else 
	{
		cosi = fabs(cosi);
		cost = sqrt(max(0.0, 1 - pow(sint, 2)));
		rs = ((n * cosi) - (r.ior * cost)) / ((n * cosi) + (r.ior * cost));	
		n = ((r.ior * cosi) - (n * cost)) / ((r.ior * cosi) + (n * cost));
		return ((rs * rs + n * n) / 2);
	}
}

