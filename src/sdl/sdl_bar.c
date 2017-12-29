/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_bar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:21:10 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/29 18:56:30 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sdl_func.h"

static void			fill_loading_bar(float ld, SDL_Rect r, t_env *e)
{
	int				width;

	width = (e->win.w * ld) / 10;
	r.w = width;
	SDL_SetRenderDrawColor(e->win.rend, 0, 0, 0, 255 );
	SDL_RenderClear(e->win.rend);
	SDL_SetRenderDrawColor(e->win.rend, ld * 255, 0, 1 - ld * 255, 255);
	SDL_RenderFillRect(e->win.rend, &r);
	SDL_RenderPresent(e->win.rend);
}

void				render_loading_bar(int tile, int tiles_num, t_env *e)
{
	static float	max_count;
	static SDL_Rect	r;
	float			ld;

	if (!max_count)
	{
		max_count = 1.f / tiles_num;
		r.x = e->win.w / 2 - (e->win.w / 10);
		r.y = e->win.h / 2 - 10;
		r.h = 20;
	}
	ld = tile * max_count;
	if ((int)(ld * 100) % 15 == 0)
		fill_loading_bar(ld, r, e);
}
