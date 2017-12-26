/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:41:29 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/26 16:39:50 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "light.h"
#include "ray.h"
#include "rt.h"
#include "rt_multithread.h"

t_geo				*geo = NULL;
static int			onclick = 0;

static int			check_drag_event(SDL_Event event, t_env *e)
{
	t_hp			hp;
	t_ray			r;
	double			x;
	double			y;

	if (event.type == SDL_MOUSEBUTTONUP)
		onclick = 0;
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		x = event.motion.x;
		y = event.motion.y;
		r = init_ray(gen_ray_origin(*e->cam->cam_to_world, *e->cam->pos), \
		gen_ray_direction(x, y, e), 1, 1.0);
		geo = ray_hit(&r, &hp, NULL, e);
		onclick = 1;
	}
	if (geo && onclick && event.type == SDL_MOUSEMOTION)
	{
		x = (2 * (event.motion.x + 0.5) / e->scr.nx - 1) * e->scr.scale;
		y = (1 - 2 * (event.motion.y + 0.5) / e->scr.ny) * e->scr.scale * 1 / e->scr.asp_ratio;
		geo->origin->x = x;
		geo->origin->y = y;
		return (1);
	}
	return (0);
}
static int			check_trans_event(SDL_Keycode k, t_env *e)
{
	int				trans;

	trans = 0;
	if (k == SDLK_DOWN && (trans = 1))
		e->cam->pos->y += 0.1;
	if (k == SDLK_UP && (trans = 1))
		e->cam->pos->y -= 0.1;
	if (k == SDLK_LEFT && (trans = 1))
		e->cam->pos->x += 0.1;
	if (k == SDLK_RIGHT && (trans = 1))
		e->cam->pos->x -= 0.1;
	if (k == SDLK_PAGEDOWN && (trans = 1))
		e->cam->pos->z += 0.1;
	if (k == SDLK_PAGEUP && (trans = 1))
		e->cam->pos->z -= 0.1;
	return (trans);
}

static int			check_rot_event(SDL_Keycode k, t_env *e)
{
	int				rot;

	rot = 0;
	if (k == SDLK_e && (rot = 1))
		cam_rot_x(e->cam->cam_to_world, M_PI / 200);
	if (k == SDLK_r && (rot = 1))
		cam_rot_x(e->cam->cam_to_world, -M_PI / 200);
	if (k == SDLK_d && (rot = 1))
		cam_rot_y(e->cam->cam_to_world, M_PI / 200);
	if (k == SDLK_f && (rot = 1))
		cam_rot_y(e->cam->cam_to_world, -M_PI / 200);
	if (k == SDLK_c && (rot = 1))
		cam_rot_z(e->cam->cam_to_world, M_PI / 200);
	if (k == SDLK_v && (rot = 1))
		cam_rot_z(e->cam->cam_to_world, -M_PI / 200);
	return (rot);
}

void				sdl_get_event(SDL_Event event, t_env *e)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (check_rot_event(event.key.keysym.sym, e))
		{
			if (!(raytrace_thread(e)))
				return ;
		}
		else if (check_trans_event(event.key.keysym.sym, e))
		{
			if (!(raytrace_thread(e)))
				return ;
		}
	}
	else if (check_drag_event(event, e))
	{
		if (!(raytrace_thread(e)))
			return ;
	}
}
