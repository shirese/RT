/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 11:26:47 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/11 16:11:13 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "rt.h"
#include "rt_multithread.h"
#include "sdl_func.h"
#include "utils.h"

void				sdl_draw_point(SDL_Renderer *rend, int x, int y, t_color c)
{
	SDL_SetRenderDrawColor(rend, \
		(int)(c.r * 255), \
		(int)(c.g * 255), \
		(int)(c.b * 255), \
		255);
	SDL_RenderDrawPoint(rend, x, y);
}

int					sdl_init(t_env **e)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0);
	else
	{
		(*e)->win.handle = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_UNDEFINED\
			, SDL_WINDOWPOS_UNDEFINED, (*e)->win.w, (*e)->win.h, 0);
		(*e)->win.rend = SDL_CreateRenderer((*e)->win.handle, -1, \
			SDL_RENDERER_ACCELERATED);
		if (!(*e)->win.handle || !(*e)->win.rend)
		{
			(*e)->win.w = 0;
			(*e)->win.h = 0;
			return (0);
		}
	}
	return (1);
}

void				sdl_render(t_env *e)
{
	SDL_Event		ev;

	print_env(e);
	raytrace(e);
	// if (!raytrace_thread(e))
	// 	return ;
	while (1 && SDL_WaitEvent(&ev))
	{
		if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)
			return ;
		else if (ev.type == SDL_QUIT)
			return ;
		else
			sdl_get_event(ev, e);
	}
}

void				sdl_stop(t_env *e)
{
	SDL_DestroyRenderer(e->win.rend);
	SDL_DestroyWindow(e->win.handle);
	SDL_Quit();
}
