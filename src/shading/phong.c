/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirese <shirese@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:03:22 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/01 22:09:32 by shirese          ###   ########.fr       */
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
		mater->ns));
	specular.g = mater->ks.g * max(0.0, pow(vec3_dot(hp.normal, reflection), \
		mater->ns));
	specular.b = mater->ks.b * max(0.0, pow(vec3_dot(hp.normal, reflection), \
		mater->ns));
	color_clamp(&specular, 0.1, 1.0);
	return (specular);
}

static t_color		calc_diffuse(t_mater *mater, double lambertian)
{
	t_color			diffuse;

	diffuse.r = mater->kd.r * max(0.0, lambertian);
	diffuse.g = mater->kd.g * max(0.0, lambertian);
	diffuse.b = mater->kd.b * max(0.0, lambertian);
	return (diffuse);
}

/*
**	[ra,ga,ba] + Σi( [Lr,Lg,Lb] ( [rd,gd,bd]max0(n•Li)
**	+ [rs,gs,bs]max0(R•Li)p ) )
*/

void				shade_phong(t_mater *mater, t_hp hp, t_light *l, t_ray *r)
{
	t_spot			*s;
	double			lambertian;

	if (l->type != 1)
	{
		s = (t_spot *)l->curr;
		lambertian = vec3_dot(hp.normal, vec3_sub_stack(*s->pos, hp.p));
		if (lambertian > 0.0)
		{
			color_add(calc_diffuse(mater, lambertian), &(r->color));
			color_add(calc_spec(mater, hp, s, r), &(r->color));
			color_mult(*l->color, &(r->color));
		}
	}
}
