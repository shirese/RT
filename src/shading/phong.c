/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:03:22 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/21 11:16:19 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "light.h"
#include "rt.h"

static t_color		calc_spec(t_geo *geo, t_hp hp, void *l, t_ray *r)
{
	t_vec3			v;
	t_vec3			reflection;
	t_color			specular;
	t_spot			*spot;
	double			spec;

	spot = l;
	v = vec3_sub_stack(r->origin, hp.p);
	reflection = vec3_reflection(l, hp);
	spec = pow(vec3_dot(hp.normal, reflection), 32.);
	if (geo->shader_type == 2)
		spec = spec > 0.4 ? 1. : 0.;
	specular.r = geo->mater->ks.r * spec;
	specular.g = geo->mater->ks.g * spec;
	specular.b = geo->mater->ks.b * spec;
	color_clamp(&specular, 0.1, 1.0);
	return (specular);
}

static t_color		calc_diffuse(t_mater *mater, t_color c, double lambertian)
{
	t_color			diffuse_col;

	diffuse_col.r = mater->kd.r * c.r * lambertian;
	diffuse_col.g = mater->kd.g * c.g * lambertian;
	diffuse_col.b = mater->kd.b * c.b * lambertian;
	return (diffuse_col);
}

t_color				calc_ambient(t_light *light)
{
	static t_color	ambient;

	if (!light)
		return (ambient);
	ambient.r = light->color->r;
	ambient.g = light->color->g;
	ambient.b = light->color->b;
	color_clamp(&ambient, 0.0, 1.0);
	return (ambient);
}

/*
**	[ra,ga,ba] + Σi( [Lr,Lg,Lb] ( [rd,gd,bd]max0(n•Li)
**	+ [rs,gs,bs]max0(R•Li)p ) )
*/

void				shade_phong(t_geo *geo, t_hp hp, t_light *l, t_ray *r)
{
	t_spot			*s;
	double			lambertian;
	t_vec3			normal;
	t_vec3			dir;
	t_mater			*mater;

	mater = geo->mater;
	if (l->type != 1)
	{
		s = (t_spot *)l->curr;
		normal = vec3_normalize_stack(hp.normal);
		dir = vec3_normalize_stack(vec3_sub_stack(*s->pos, hp.p));
		lambertian = vec3_dot(normal, dir);
		if (geo->shader_type == 2)
			set_toon_lambertian(&lambertian);
		if (lambertian > 0.0)
		{
			if (geo->shader_type == 2 && get_toon_edges(geo->type, hp, *r))
				color_set(color_new_stack(0., 0., 0.), &(r->color));
			else
			{
				color_add(calc_diffuse(geo->mater, *l->color, lambertian), &(r->color));
				color_add(calc_spec(geo, hp, s, r), &(r->color));
			}
		}
	}
}
