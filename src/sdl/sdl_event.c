/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:41:29 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/05 12:25:10 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "geo.h"
#include "light.h"
#include "ray.h"
#include "rt.h"
#include "rt_multithread.h"
#include "sdl_func.h"

static void			sdl_save_img(t_env *e)
{
	char			*save_path;

	save_path = malloc(sizeof(char) * 50);
	ft_strncpy(save_path, "saves/", 6);
	SDL_SaveBMP(e->win.sshot, ft_strcat(save_path, SAVE_NAME));
	free(save_path);
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
		else if (event.key.keysym.sym == SDLK_p)
			sdl_save_img(e);
	}
	else if (check_drag_event(event, e))
	{
		if (!(raytrace_thread(e)))
			return ;
	}
}
