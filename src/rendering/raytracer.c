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

t_ray				init_ray(t_vec3 origin, t_vec3 direction, int ray_type)
{
	t_ray			r;

	r.origin = origin;
	r.direction = vec3_normalize_stack(direction);
	r.color = color_new_stack(0.0, 0.0, 0.0, 1.0);
	r.type = ray_type;
	if (r.type == 1)
	{
		r.origin.x += 0.000001;
		r.origin.y += 0.000001;
		r.origin.z += 0.000001;
	}
	return (r);
}

void				color_of_ray(t_env *env, t_ray *r, int rec)
{
	t_geo		*geo;
	t_geo		*g;
	t_light		*l;
	t_hp		hp;
	int			nb_sum;

	nb_sum = 0;

	geo = ray_hit(r, &hp, NULL, env);
	apply_lights_beta(r, geo, hp, env);
	if (geo != NULL && rec < MAX_RECURSION)
	{
		l = env->lights;
		g = env->geos;
		while (l)
		{
			nb_sum++;
			if (l->type != 1)
			{

			}
			l = l->next;
		}
	}
}

static t_color		shoot_ray(double x, double y, t_env *e)
{
	t_geo			*geo;
	t_hp			hp;
	t_ray			r;

	geo = NULL;
	r = init_ray(gen_ray_origin(*e->cam->cam_to_world, *e->cam->pos), \
		gen_ray_direction(x, y, e), 0);
	color_of_ray(e, &r, 0);
	return (r.color);
}

t_color				get_px_col(int x, int y, t_env *e)
{
	double			ij[2];
	double			px_pos[2];
	static double	samp_count;
	t_color			px_col;

	if (e->samp_rate == 1)
		return (shoot_ray(x, y, e));
	px_col = color_new_stack(0., 0., 0., 1.);
	ij[0] = 0;
	if (!samp_count)
		samp_count = 1 / (pow((e->samp_rate / 2), 2));
	while (ij[0]++ < e->samp_rate / 2)
	{
		ij[1] = 0;
		while (ij[1]++ < e->samp_rate / 2)
		{
			px_pos[0] = x + ij[0] / (e->samp_rate / 2);
			px_pos[1] = y + ij[1] / (e->samp_rate / 2);
			color_add_no_clamp(shoot_ray(px_pos[0], px_pos[1], e), &px_col);
		}
	}
	px_col.r *= samp_count;
	px_col.g *= samp_count;
	px_col.b *= samp_count;
	return (px_col);
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
			c = shoot_ray(x, y, e);
			sdl_draw_point(e->win.rend, x, y, c/*get_px_col(x, y, e)*/);
			x++;
		}
		y++;
	}
	SDL_UpdateWindowSurface(e->win.handle);
	SDL_RenderPresent(e->win.rend);
}
