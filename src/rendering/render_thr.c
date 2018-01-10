/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:13:06 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/10 13:04:42 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "rt_multithread.h"
#include "sdl_func.h"

static void			render_px(t_env *e)
{
	int				x;
	int				y;
	t_color			px_col;

	y = 0;
	while (y < e->win.h)
	{
		x = 0;
		while (x < e->win.w)
		{
			px_col = e->img[y * e->scr.nx + x];
			if (e->filter != 0)
				apply_filters(&px_col, e);
			sdl_draw_point(e->win.rend, x, y, px_col);
			x++;
		}
		y++;
	}
	SDL_RenderReadPixels(e->win.rend, NULL, SDL_PIXELFORMAT_ARGB8888, \
		e->win.sshot->pixels, e->win.sshot->pitch);
	SDL_RenderPresent(e->win.rend);
}

static void			compute_tile_px(int *tile_xy, int tile, t_env *e)
{
	int				i;
	int				j;
	int				x;
	int				y;

	j = 0;
	x = tile_xy[0] * (tile % (e->win.w / tile_xy[0]));
	y = tile_xy[1] * (tile / (e->win.w / tile_xy[0]));
	while (j < tile_xy[1])
	{
		i = 0;
		while (i < tile_xy[0])
		{
			e->img[e->win.w * (y + j) + (x + i)] = get_px_col(x + i, y + j, e);
			i++;
		}
		j++;
	}
}

static int			handle_t(int *t_xy, int *t, int t_n, t_thread_data *thr_dt)
{
	*t = __sync_add_and_fetch(&thr_dt->tile_id, 1) - 1;
	if (*t >= t_n)
		return (0);
	if (!SDL_LockMutex(thr_dt->mutex))
	{
		if (thr_dt->ld_done == 0)
			render_loading_bar(*t, t_n, thr_dt->e);
		compute_tile_px(t_xy, *t, thr_dt->e);
		SDL_UnlockMutex(thr_dt->mutex);
	}
	return (1);
}

/*
**	__sync_add_and_fetch atomically increment tile_id so that each thread
**	works on a different tile.
*/

static int			render_tile(void *arg)
{
	t_thread_data	*thr_data;
	int				tile_xy[2];
	int				tile;
	int				tiles_num;

	thr_data = (t_thread_data *)arg;
	tile = 0;
	tile_xy[0] = find_factor(thr_data->e->win.w, TILESIZE);
	tile_xy[1] = find_factor(thr_data->e->win.h, TILESIZE);
	if (!tile_xy[0] || !tile_xy[1])
	{
		ft_putendl("Invalid resolution.");
		return (0);
	}
	tiles_num = (thr_data->e->win.w / tile_xy[0]) * \
		(thr_data->e->win.h / tile_xy[1]);
	while (1)
	{
		if (!handle_t(tile_xy, &tile, tiles_num, thr_data))
			break ;
	}
	return (0);
}

int					raytrace_thread(t_env *e)
{
	SDL_Thread		*thr;
	t_thread_data	thr_data;
	static int		first_load;
	char			*thr_name;
	int				i;

	i = -1;
	thr_name = NULL;
	thr_data.tile_id = 0;
	thr_data.ld_done = first_load;
	thr_data.mutex = SDL_CreateMutex();
	thr_data.e = e;
	while (++i < NUM_THREADS)
	{
		thr_name = ft_itoa(i);
		if ((!(thr = SDL_CreateThread(render_tile, thr_name, &thr_data))))
			ft_printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		else
			SDL_WaitThread(thr, NULL);
		free(thr_name);
	}
	SDL_DestroyMutex(thr_data.mutex);
	first_load = 1;
	render_px(e);
	return (1);
}
