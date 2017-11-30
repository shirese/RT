/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirese <shirese@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 11:26:47 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/30 21:45:13 by shirese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "rt.h"
#include "rt_multithread.h"
#include "utils.h"

void				sdl_draw_point(SDL_Renderer *rend, int x, int y, t_color c)
{
	SDL_SetRenderDrawColor(rend, \
		(int)(c.r * 255), \
		(int)(c.g * 255), \
		(int)(c.b * 255), \
		(int)(c.a * 255));
	SDL_RenderDrawPoint(rend, x, y);
}

t_env				*sdl_init(t_env *e)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
		return (NULL);
	else
	{
		e->win.handle = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, \
			SDL_WINDOWPOS_UNDEFINED, e->win.width, e->win.height, SDL_WINDOW_BORDERLESS);
		if (!e->win.handle)
		{
			ft_printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
			return (NULL);
		}
		e->win.rend = SDL_CreateRenderer(e->win.handle, -1, SDL_RENDERER_SOFTWARE);
		if (!e->win.rend)
		{
			ft_printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
			return (NULL);
		}
	}
	return (e);
}

void				sdl_render(t_env *e)
{
	SDL_Event		ev;

	print_env(e);
	if (!raytrace_thread(e))
		return ;
	while (1 && SDL_WaitEvent(&ev))
	{
		// if (ev.type == SDL_WINDOWEVENT_RESIZED)
		// {
		// 	SDL_RenderClear(e->win.rend);
		// 	if (!raytrace_thread(e))
		// 		return ;
		// }
		// else if (ev.type == SDL_WINDOWEVENT_MAXIMIZED)
		// {
		// 	SDL_RenderClear(e->win.rend);
		// 	raytrace(e);
		// 	return ;
		// }
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
