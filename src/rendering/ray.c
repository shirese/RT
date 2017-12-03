/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 14:34:15 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/06 12:38:46 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "matrice.h"
#include "rt.h"

t_vec3				point_at_parameter(double t, t_ray r)
{
	t_vec3			pap;
	t_vec3			tmp;

	tmp = vec3_mult_stack(r.direction, t);
	pap = vec3_add_stack(r.origin, tmp);
	return (pap);
}

static int			is_nearest(t_hp latest_hp, t_hp *hp, double *md)
{
	double			dist;

	dist = vec3_norm(latest_hp.p);
	if (dist < *md)
	{
		*md = dist;
		*hp = latest_hp;
		return (1);
	}
	return (0);
}

t_geo				*ray_hit(t_ray *r, t_hp *hp, t_geo *from, t_env *e)
{
	double			min_dist;
	t_hp			latest_hp;
	t_ray			tr;
	t_geo			*geo;
	t_geo			*nearest_geo;

	min_dist = INFINITY;
	geo = e->geos;
	nearest_geo = NULL;
	
	while (geo != NULL)
	{
		tr = *r;
		if (geo != from)
		{
			latest_hp = geo->is_hit(geo, tr);
			if (latest_hp.t != -1 && is_nearest(latest_hp, hp, &min_dist) && (r->type != 2 || geo->mater->kd.a != 0.0))
				nearest_geo = geo;
		}
		geo = geo->next;
	}
	return (nearest_geo);
}

t_vec3				gen_ray_direction(double i, double j, t_env *e)
{
	double			x;
	double			y;
	t_vec3			ray_direction;

	x = (2 * (i + 0.5) / e->scr.nx - 1) * e->scr.scale;
	y = (1 - 2 * (j + 0.5) / e->scr.ny) * e->scr.scale * 1 / e->scr.asp_ratio;
	ray_direction = mat4_mult_vec(*e->cam->cam_to_world, vec3_stack(x, y, -1.));
	vec3_normalize(&ray_direction);
	return (ray_direction);
}

t_vec3				gen_ray_origin(t_mat4 cam_to_world, t_vec3 cam_origin)
{
	t_vec3			ray_origin;

	ray_origin = mat4_mult_vec(cam_to_world, cam_origin);
	return (ray_origin);
}
