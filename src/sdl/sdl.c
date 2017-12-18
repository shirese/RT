/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 11:26:47 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/14 12:23:02 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt.h"
#include "rt_multithread.h"
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

t_env				*sdl_init(t_env *e)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
		return (NULL);
	else
	{
		SDL_CreateWindowAndRenderer(e->win.w, e->win.h, \
			SDL_WINDOW_RESIZABLE, &(e->win.handle), &(e->win.rend));
		if (!e->win.handle)
		{
			e->win.w = 0;
			e->win.h = 0;
		}
		else
			SDL_SetWindowTitle(e->win.handle, WIN_TITLE);
		if (e->win.w == 0 || e->win.h == 0)
			return (NULL);
	}
	return (e);
}

void				sdl_render(t_env *e)
{
	SDL_Event		ev;

	
	print_env(e);
	raytrace(e);
	/*if (!raytrace_thread(e))
		return ;*/
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
