/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_ref.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:04:54 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/13 15:18:41 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ray.h"
#include "light.h"
#include "pthread.h"
#include "rt.h"
#include "utils.h"

t_color			throw_reflect_ray(t_ray *r, t_hp hp, t_geo *from, t_env *e)
{
	t_ray		refl;

	refl = reflect_ray(*r, hp);
	refl.rec = r->rec;
	if (refl.type != 0)
	{
		color_mult_fac(&r->color, 1. - from->mater->reflectivity);
		throw_ray(&refl, e);
		color_mult_fac(&refl.color, from->mater->reflectivity);
	}
	else
		r->rec--;
	return (refl.color);
}

t_color			throw_refract_ray(t_ray *r, t_hp hp, t_env *e)
{
	t_ray			refr;

	refr = refract_ray(e->geos, *r, hp);
	refr.rec = r->rec;
	if (refr.type != 0)
		throw_ray(&refr, e);
	else
		r->rec--;
	return (refr.color);
}

void				throw_new_rays(t_ray *r, t_hp hp, t_geo *from, t_env *e)
{
	double			kr;
	t_color			refr_col;
	t_color			refl_col;

	kr = find_krefl(from, hp, *r);
	refr_col = color_new_stack(0., 0., 0.);
	if (kr < 1.)
	{
		r->rec++;
		refr_col = throw_refract_ray(r, hp, e);
		color_mult_fac(&refr_col, (1 - kr));
	}
	r->rec++;
	refl_col = throw_reflect_ray(r, hp, from, e);
	color_mult_fac(&refl_col, kr);
	color_add(refl_col, &(r->color));
	color_add(refr_col, &(r->color));
}
