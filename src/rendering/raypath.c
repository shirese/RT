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
		else if (g->type == 3)
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
			if (belong_to_pipe(g, pos) == 1)
				return (g->mater->ior);
		}
		g = g->next;	
	}
	return (1.0);
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


void				fresnel(t_ray r, t_hp hp, double n, double *krefl)
{
	t_vec3 normal;
	double cosi;
	double etai;
	double etat;
	double sint;
	double cost;
	double rs;
	double rp;

	r.direction = vec3_normalize_stack(r.direction);
	normal = vec3_normalize_stack(hp.normal);
	cosi = clamp(vec3_dot(r.direction, normal), -1, 1);
	etai = r.ior;
	etat = n;
	sint = (etai / etat) * sqrt(max(0, 1 - pow(cosi, 2)));
	if (sint >= 1.0)
		*krefl = 1;
	else 
	{
		cosi = fabs(cosi);
		cost = sqrt(max(0.0, 1 - pow(sint, 2)));
		rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));	
		rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*krefl = (rs * rs + rp * rp) / 2;
	}
}
