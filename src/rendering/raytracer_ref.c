/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_ref.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:04:54 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 12:25:37 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "color.h"
#include "ray.h"
#include "light.h"
#include "pthread.h"
#include "rt.h"
#include "utils.h"

void				throw_reflect_ray(t_ray *r, t_hp hp, double k_refl, t_env *e)
{
	t_ray refl;

	refl = reflect_ray(*r, hp);
	refl.rec = r->rec;
	if (refl.type != 0)
	{
		throw_ray(&refl, e);
		color_mult_fac(&(refl.color), k_refl);
		color_add(refl.color, &(r->color));
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
		color_add(refr.color, &(r->color));
	}
	else
		r->rec--;
}

void				throw_new_rays(t_ray *r, t_hp hp, double k_refl, t_env *e)
{
	if (k_refl < 1.)
	{
		r->rec++;
		throw_refract_ray(r, hp, k_refl, e);
	}
	r->rec++;
	throw_reflect_ray(r, hp, k_refl, e);
}
