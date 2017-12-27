/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_bar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:21:10 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/27 17:48:52 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sdl_func.h"

void				render_loading_bar(int tile, int tiles_num, t_env *e)
{
	static int		loading_done;
	static float	max_count;
	static SDL_Rect	r;
	int				width;
	float			progress;

	if (loading_done)
		return ;
	if (!max_count)
	{
		max_count = 1.f / tiles_num;
		r.x = e->win.w / 2 - (e->win.w / 10);
		r.y = e->win.h / 2 - 10;
		r.h = 20;
	}
	progress = tile * max_count;
	width = (e->win.w * progress) / 10;
	r.w = width;
	SDL_SetRenderDrawColor(e->win.rend, 0, 0, 0, 255 );
	SDL_RenderClear(e->win.rend);
	SDL_SetRenderDrawColor(e->win.rend, progress * 255, 0, \
		1 - progress * 255, 255);
	SDL_RenderFillRect(e->win.rend, &r);
	SDL_RenderPresent(e->win.rend);
	if (progress >= 0.999000)
		loading_done = 1;
}
