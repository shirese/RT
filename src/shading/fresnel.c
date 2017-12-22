/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 12:03:50 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 17:25:36 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ray.h"
#include "light.h"
#include "pthread.h"
#include "rt.h"
#include "utils.h"
#include "geo.h"

double				ior_at_point(t_geo *geo, t_vec3 pos)
{
	t_geo			*g;
	double			res;

	res = 0;
	g = geo;
	while (g)
	{
		if (belong_to(g, pos))
			return (g->mater->ior);
		g = g->next;
	}
	return (1.0);
}

double				find_ior(t_geo *geo, t_ray r, t_hp hp)
{
	t_geo			*g;
	t_vec3			diff;
	t_vec3			eps;
	t_vec3			i;
	double			len;

	g = geo;
	diff = vec3_sub_stack(hp.p, r.origin);
	len = vec3_norm(diff);
	i = r.dir;
	i = vec3_normalize_stack(i);
	eps = vec3_add_mult_stack(r.origin, i, len + EPSILON);
	return (ior_at_point(geo, eps));
}

double				find_krefl(t_geo *geo, t_hp hp, t_ray r)
{
	if (geo->mater->illum == 2)
		return (1);
	else if (geo->mater->illum == 3)
		return (0);
	else if (geo->mater->illum == 4)
		return (coeff_fresnel(r, hp, geo));
	return (-1);
}

double				coeff_fresnel(t_ray r, t_hp hp, t_geo *geo)
{
	double			cosi;
	double			sint;
	double			cost;
	double			rs;
	double			n;

	n = find_ior(geo, r, hp);
	r.dir = vec3_normalize_stack(r.dir);
	cosi = clamp(vec3_dot(r.dir, vec3_normalize_stack(hp.normal)), -1, 1);
	sint = (r.ior / n) * sqrt(max(0, 1 - cosi * cosi));
	if (sint >= 1.0)
		return (1);
	else
	{
		cosi = fabs(cosi);
		cost = sqrt(max(0.0, 1 - sint * sint));
		rs = ((n * cosi) - (r.ior * cost)) / ((n * cosi) + (r.ior * cost));
		n = ((r.ior * cosi) - (n * cost)) / ((r.ior * cosi) + (n * cost));
		return ((rs * rs + n * n) / 2);
	}
}
