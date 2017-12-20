/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:04:54 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/18 11:44:52 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "ray.h"
#include "light.h"
#include "pthread.h"
#include "rt.h"
#include "texture.h"
#include "utils.h"

static int			is_nearest(t_hp latest_hp, t_hp *hp, double *md)
{
	double			dist;

	dist = vec3_norm(latest_hp.p);
	if (dist < *md)
	{
		*md = dist;
		*hp = latest_hp;
		return (1);
	}
	return (0);
}

t_geo				*ray_hit(t_ray *r, t_hp *hp, t_geo *from, t_env *e)
{
	double			min_dist;
	t_hp			latest_hp;
	t_ray			tr;
	t_geo			*geo;
	t_geo			*nearest_geo;

	min_dist = INFINITY;
	geo = e->geos;
	nearest_geo = NULL;
	while (geo != NULL)
	{
		tr = *r;
		if (geo != from)
		{
			latest_hp = geo->is_hit(geo, tr);
			if (latest_hp.t != -1 && is_nearest(latest_hp, hp, &min_dist))
				nearest_geo = geo;
		}
		geo = geo->next;
	}
	return (nearest_geo);
}

void				throw_ray(t_ray *r, t_env *e)
{
	t_geo			*geo;
	t_hp			hp;

	geo = ray_hit(r, &hp, NULL, e);
	if (r->type != 3)
		apply_ambient_light(r, e);
	if (geo)
	{
		if (geo->tex)
			apply_texture(r, &hp, geo);
		apply_lights(r, geo, hp, e);
	}
}

t_color				find_ray_color(double x, double y, t_env *e)
{
	t_geo			*geo;
	t_ray			r;

	geo = NULL;
	r = init_ray(gen_ray_origin(*e->cam->cam_to_world, *e->cam->pos), \
		gen_ray_direction(x, y, e), 1, 1.0);
	throw_ray(&r, e);
	return (r.color);
}

void				raytrace(t_env *e)
{
	t_color			c;
	int				x;
	int				y;

	SDL_RenderClear(e->win.rend);
	y = 0;
	while (y < e->scr.ny)
	{
		x = 0;
		while (x < e->scr.nx)
		{
			c = find_ray_color(x, y, e);
			sdl_draw_point(e->win.rend, x, y, c);
			x++;
		}
		y++;
	}
	SDL_UpdateWindowSurface(e->win.handle);
	SDL_RenderPresent(e->win.rend);
}
