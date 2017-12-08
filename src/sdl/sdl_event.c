/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:41:29 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/08 10:21:56 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_multithread.h"

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
}
