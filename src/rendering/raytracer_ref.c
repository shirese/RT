/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_ref.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:04:54 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/08 08:33:30 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "color.h"
#include "ray.h"
#include "light.h"
#include "pthread.h"
#include "rt.h"
#include "utils.h"

void				translate_ray(t_ray *r, t_hp hp)
{
	r->direction = vec3_normalize_stack(r->direction);
	r->origin = vec3_sub_stack(hp.p, r->direction);
}

void				throw_reflect_ray(t_ray *r, t_hp hp, double k_refl, t_env *e)
{
	t_ray refl;

	refl = reflect_ray(*r, hp);
	refl.rec = r->rec;
	if (refl.type != 0)
	{
		throw_ray(&refl, e);
		color_mult_fac(&(refl.color), k_refl);
		color_add_no_clamp(refl.color, &(r->color));
	}
	else
		r->rec--;
}

void				throw_refract_ray(t_ray *r, t_hp hp, double k_refl, t_env *e)
{
	t_ray			refr;

	refr = refract_ray(e->geos, *r, hp);
	refr.rec = r->rec;
	if (refr.type != 0)
	{
		throw_ray(&refr, e);
		color_mult_fac(&(refr.color), (1 - k_refl));
		color_add_no_clamp(refr.color, &(r->color));
	}
	else
		r->rec--;
}

void				throw_new_rays(t_ray *r, t_hp hp, double k_refl, t_env *e)
{
	if (k_refl > 0)
		throw_reflect_ray(r, hp, k_refl, e);
	if (1 - k_refl > 0)
		throw_refract_ray(r, hp, k_refl, e);
}
