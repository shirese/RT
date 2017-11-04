/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 12:20:53 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/18 18:17:54 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "light.h"
#include "ray.h"
#include "rt.h"
#include "vector.h"

static int			has_shadow(void *light, t_vec3 hp_pos, t_geo *geo, t_env *e)
{
	t_geo			*shadow_geo;
	t_hp			shadow_hp;
	t_vec3			light_dir;
	t_ray			shadow_ray;
	t_spot			*spot;

	shadow_geo = NULL;
	spot = light;
	light_dir = vec3_sub_stack(*spot->pos, hp_pos);
	shadow_ray = shoot_ray(hp_pos, light_dir, 1);
	shadow_geo = ray_hit(&shadow_ray, &shadow_hp, geo, e);
	if (shadow_geo && shadow_hp.t <= vec3_norm(light_dir))
		return (1);
	return (0);
}

void				apply_lights(t_ray *r, t_geo *geo, t_hp hp, t_env *e)
{
	t_light			*light;

	light = e->lights;
	while (light != NULL)
	{
		if (light->type == 1)
			color_add(calc_ambient(light), &(r->color));
		else if (geo && r->type == 0)
		{
			if (has_shadow(light->curr, hp.p, geo, e) == 1)
				color_mult(calc_ambient(light), &(r->color));
			else if (has_shadow(light->curr, hp.p, geo, e) == 2)
				color_set(color_new_stack(1., 0., 0., 1.), &(r->color));
			else if (has_shadow(light->curr, hp.p, geo, e) == 3)
				color_set(color_new_stack(0., 1., 0., 1.), &(r->color));
			else
				shade_phong(geo->mater, hp, light, r);
		}
		light = light->next;
	}
}
