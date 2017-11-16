/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 12:20:53 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/16 13:47:33 by chaueur          ###   ########.fr       */
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
	shadow_ray = init_ray(hp_pos, light_dir, 1);
	shadow_geo = ray_hit(&shadow_ray, &shadow_hp, geo, e);
	if (shadow_geo && shadow_hp.t <= vec3_norm(light_dir))
		return (1);
	return (0);
}

void				apply_ambient_light(t_ray *r, t_env *e)
{
	static int		is_set;
	static t_color	ambient;
	int				i;
	t_light			*light;

	if (is_set)
		color_set(ambient, &(r->color));
	else
	{
		i = 1;
		is_set = 1;
		light = e->lights;
		ambient = color_new_stack(0., 0., 0., 1.);
		while (light != NULL)
		{
			if (light->type == 1)
			{
				color_add(*light->color, &ambient);
				color_div_fac(&ambient, i);
				i++;
			}
			light = light->next;
		}
		color_set(ambient, &(r->color));
	}
}

void				apply_lights(t_ray *r, t_geo *geo, t_hp hp, t_env *e)
{
	t_light			*light;

	light = e->lights;
	while (light != NULL)
	{
		if (light->type != 1 && r->type == 0)
		{
			if (has_shadow(light->curr, hp.p, geo, e) == 1)
				color_mult(*light->color, &(r->color));
			else
				shade_phong(geo->mater, hp, light, r);
		}
		light = light->next;
	}
}
