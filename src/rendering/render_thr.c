/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:13:06 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/04 14:53:28 by chaueur          ###   ########.fr       */
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
	SDL_UpdateWindowSurface(e->win.handle);
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
	pthread_mutex_lock(&thr_dt->mutex);
	if (thr_dt->ld_done == 0)
		render_loading_bar(*t, t_n, thr_dt->e);
	compute_tile_px(t_xy, *t, thr_dt->e);
	pthread_mutex_unlock(&thr_dt->mutex);
	return (1);
}

/*
**	__sync_add_and_fetch atomically increment tile_id so that each thread
**	works on a different tile.
*/

static void			*render_tile(void *arg)
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
		ft_printf("Invalid resolution.\n");
		pthread_exit(NULL);
	}
	tiles_num = (thr_data->e->win.w / tile_xy[0]) * \
		(thr_data->e->win.h / tile_xy[1]);
	while (1)
	{
		if (!handle_t(tile_xy, &tile, tiles_num, thr_data))
			break ;
	}
	pthread_exit(NULL);
}

int					raytrace_thread(t_env *e)
{
	pthread_t		thr[NUM_THREADS];
	t_thread_data	thr_data;
	static int		first_load;
	int				i;

	i = -1;
	thr_data.tile_id = 0;
	thr_data.ld_done = first_load;
	pthread_mutex_init(&thr_data.mutex, NULL);
	thr_data.e = e;
	while (++i < NUM_THREADS)
	{
		if ((pthread_create(&thr[i], NULL, render_tile, &thr_data)))
		{
			ft_printf("Error while creating thread.\n");
			exit(-1);
		}
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(thr[i], NULL);
	pthread_mutex_destroy(&thr_data.mutex);
	first_load = 1;
	render_px(e);
	return (1);
}
