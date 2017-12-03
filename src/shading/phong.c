/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:03:22 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/08 17:45:23 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "light.h"
#include "rt.h"

static t_color		calc_spec(t_mater *mater, t_hp hp, void *l, t_ray *r)
{
	t_vec3			v;
	t_vec3			reflection;
	t_color			specular;
	t_spot			*spot;

	spot = l;
	v = vec3_sub_stack(r->origin, hp.p);
	reflection = vec3_reflection(l, hp);
	specular.r = mater->ks.r * max(0.0, pow(vec3_dot(hp.normal, reflection), \
		2.));
	specular.g = mater->ks.g * max(0.0, pow(vec3_dot(hp.normal, reflection), \
		2.));
	specular.b = mater->ks.b * max(0.0, pow(vec3_dot(hp.normal, reflection), \
		2.));
	specular.a = 1.0;
	color_clamp(&specular, 0.1, 1.0);
	return (specular);
}

static t_color		calc_diffuse(t_mater *mater, double lambertian)
{
	t_color			diffuse;

	diffuse.r = mater->kd.r * max(0.0, lambertian);
	diffuse.g = mater->kd.g * max(0.0, lambertian);
	diffuse.b = mater->kd.b * max(0.0, lambertian);
	//printf("Diffuse %f %f %f",diffuse.r, diffuse.g, diffuse.b);
	diffuse.a = 1.0;
	return (diffuse);
}

t_color				calc_ambient(t_light *light)
{
	static t_color	ambient;

	if (!light)
		return (ambient);
	ambient.r = light->color->r;
	ambient.g = light->color->g;
	ambient.b = light->color->b;
	//clamp_color(&ambient, 0.0, 1.0);
	color_clamp(&ambient, 0.0, 1.0);
	return (ambient);
}

/*
**	[ra,ga,ba] + Σi( [Lr,Lg,Lb] ( [rd,gd,bd]max0(n•Li)
**	+ [rs,gs,bs]max0(R•Li)p ) )
*/

void				shade_phong(t_geo	*geo/*t_mater *mater*/, t_hp hp, t_light *l, t_ray *r)
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
		if (geo->type == 7)
			lambertian = fabs(lambertian);
		if (lambertian > 0.0)
		{
			//puts("souci");
			color_add(calc_diffuse(mater, lambertian), &(r->color));
			color_add(calc_spec(mater, hp, s, r), &(r->color));
			color_mult(*l->color, &(r->color));
		}
		/*else if (mater->kd.a == 0.0)
		{
			//puts("Phong_transp");
			//color_add_mult(calc_diffuse(mater, lambertian), &(r->color), 0.1);
			//printf("LAMBERTIAN %f\n", lambertian);
			//color_print(r->color);
			color_add(calc_diffuse(mater, lambertian), &(r->color));
			//color_print(calc_diffuse(mater, lambertian));
			//color_print(r->color);
			//color_add_mult(calc_spec(mater, hp, s, r), &(r->color), 0.1);
			//color_mult(*l->color, &(r->color));
		}*/
	}
}
