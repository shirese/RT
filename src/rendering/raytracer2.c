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

int					reflect_or_refract(t_geo *geo)
{
	return ((geo->mater->kg.g == 1.0 || geo->mater->kg.b == 1.0 || geo->mater->kg.a == 1.0));
}

void				translate_ray(t_ray *r, t_hp hp)
{
	r->direction = vec3_normalize_stack(r->direction);
	r->origin = vec3_sub_stack(hp.p, r->direction);
}

void				throw_reflect_ray(t_ray *r, t_hp hp, t_env *env, double k_refl)
{
	t_ray refl;

	refl = reflect_ray(*r, hp);
	refl.rec = r->rec;
	if (refl.type != 0)
    {
		color_of_ray(env, &refl);
    	color_add_mult((refl.color), &(r->color), k_refl);
	}
	else
		r->rec--;
}

void				throw_refract_ray(t_ray *r, t_hp hp, t_env *env, double k_refl)
{
	t_ray refr;
	t_geo *g;

	g = env->geos;
	refr = refract_ray(g, *r, hp);
	refr.rec = r->rec;
	if (refr.type != 0)
    {
        color_of_ray(env, &refr);
		color_add_mult((refr.color), &(r->color), (1 - k_refl));
	}
	else
		r->rec--;
}

void				throw_new_rays(t_env *env, t_ray *r, t_hp hp, double k_refl)
{
	if (k_refl > 0)
		throw_reflect_ray(r, hp, env, k_refl);
	if (1 - k_refl > 0)
		throw_refract_ray(r, hp, env, k_refl);
}
