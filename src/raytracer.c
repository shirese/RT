/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:04:54 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/04 15:41:29 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "light.h"
#include "rt.h"
#include "utils.h"

t_ray				shoot_ray(t_vec3 origin, t_vec3 direction, int ray_type)
{
	t_ray			r;

	r.origin = origin;
	r.direction = vec3_normalize_stack(direction);
	r.color = color_new_stack(0.0, 0.0, 0.0, 1.0);
	r.type = ray_type;
	if (r.type == 1)
	{
		r.origin.x += 0.001;
		r.origin.y += 0.001;
		r.origin.z += 0.001;
	}
	return (r);
}

void				raytrace(t_env *e)
{
	int				x;
	int				y;
	t_geo			*geo;
	t_hp			hp;
	t_ray			r;

	SDL_RenderClear(e->win.rend);
	y = 0;
	
	while (y < e->scr.ny)
	{
		x = 0;
		while (x < e->scr.nx)
		{
			r = shoot_ray(gen_ray_origin(*e->cam->cam_to_world, *e->cam->pos), \
				gen_ray_direction(x, y, e), 0);
			geo = ray_hit(&r, &hp, NULL, e);	
			apply_lights(&r, geo, hp, e);
			sdl_draw_point(e->win.rend, x, y, r.color);
			x++;
		}
		y++;
	}
	SDL_UpdateWindowSurface(e->win.handle);
	SDL_RenderPresent(e->win.rend);
}
