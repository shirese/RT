/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:13:06 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/15 11:27:55 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "rt_multithread.h"

static void			render_px(t_env *e)
{
	int				x;
	int				y;

	y = 0;
	while (y < e->win.h)
	{
		x = 0;
		while (x < e->win.w)
		{
			sdl_draw_point(e->win.rend, x, y, e->img[y * e->win.w + x]);
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

static int			find_factor(int n, int f)
{
	int				i;

	i = 0;
	while (i < TILESIZE)
	{
		if (n % (f - i) == 0)
			return (f - i);
		else if (n % (f + i) == 0)
			return (f + i);
		i++;
	}
	return (0);
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
		tile = __sync_add_and_fetch(&thr_data->tile_id, 1) - 1;
		if (tile >= tiles_num)
			break ;
		compute_tile_px(tile_xy, tile, thr_data->e);
	}
	pthread_exit(NULL);
}

int					raytrace_thread(t_env *e)
{
	pthread_t		thr[NUM_THREADS];
	t_thread_data	thr_data;
	int				i;
	int				rc;

	i = 0;
	thr_data.tile_id = 0;
	pthread_mutex_init(&thr_data.mutex, NULL);
	thr_data.e = e;
	while (i < NUM_THREADS)
	{
		if ((rc = pthread_create(&thr[i], NULL, render_tile, &thr_data)))
		{
			ft_printf("Error while creating thread.\n");
			return (0);
		}
		i++;
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(thr[i], NULL);
	render_px(e);
	pthread_mutex_destroy(&thr_data.mutex);
	return (1);
}
