/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:03:22 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/21 16:01:06 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "light.h"
#include "rt.h"

static t_color		calc_spec(t_mater *mater, t_hp hp, t_light *l, t_ray *r)
{
	t_vec3			v;
	t_vec3			reflection;
	t_color			specular;

	v = vec3_sub_stack(r->origin, hp.p);
	reflection = vec3_reflection(get_light_pos(hp.p, l), hp);
	specular.r = mater->ks.r * max(0.0, pow(vec3_dot(hp.normal, reflection), \
		32.));
	specular.g = mater->ks.g * max(0.0, pow(vec3_dot(hp.normal, reflection), \
		32.));
	specular.b = mater->ks.b * max(0.0, pow(vec3_dot(hp.normal, reflection), \
		32.));
	specular.a = 1.0;
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
	double			lambertian;
	t_vec3			light_dir;
	t_mater			*mater;

	mater = geo->mater;
	if (l->type != 1)
	{
		light_dir = get_light_dir(hp.p, l);
		vec3_normalize(&light_dir);
		lambertian = vec3_dot(hp.normal, light_dir);
		if (geo->shader_type == 2)
			set_toon_lambertian(&lambertian);
		if (lambertian > 0.0)
		{
			if (geo->shader_type == 2 && get_toon_edges(geo->type, hp, *r))
				color_set(color_new_stack(0., 0., 0.), &(r->color));
			else
			{
				color_add(calc_diffuse(geo->mater, *l->color, lambertian), &(r->color));
				if (l->type != 2)
						color_add(calc_spec(geo->mater, hp, l, r), &(r->color));
			}
		}
	}
}
