/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:13:06 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/23 14:18:32 by chaueur          ###   ########.fr       */
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
	while (y < e->scr.ny)
	{
		x = 0;
		while (x < e->scr.nx)
		{
			sdl_draw_point(e->win.rend, x, y, e->img[y * e->scr.nx + x]);
			x++;
		}
		y++;
	}
	SDL_UpdateWindowSurface(e->win.handle);
	SDL_RenderPresent(e->win.rend);
}

static void			sync_tile(int tile, t_color *tile_px, t_env *e)
{
	int				i;
	int				j;
	int				x;
	int				y;

	i = 0;
	j = 0;
	x = TILESIZE * (tile % (e->scr.nx / TILESIZE));
	y = TILESIZE * (tile / (e->scr.nx / TILESIZE));
	while (j < TILESIZE)
	{
		i = 0;
		while (i < TILESIZE)
		{
			e->img[e->scr.nx * (y + j) + (x + i)] = tile_px[j * TILESIZE + i];
			i++;
		}
		j++;
	}
}

static void			compute_tile_px(int tile, t_color *tile_px, t_env *e)
{
	int				i;
	int				j;
	int				x;
	int				y;

	j = 0;
	x = TILESIZE * (tile % (e->scr.nx / TILESIZE));
	y = TILESIZE * (tile / (e->scr.nx / TILESIZE));
	while (j < TILESIZE)
	{
		i = 0;
		while (i < TILESIZE)
		{
			tile_px[j * TILESIZE + i] = get_px_col(x + i, y + j, e);
			i++;
		}
		j++;
	}
}

/*
**	__sync_add_and_fetch atomically increment tile_id so that each thread 
**	works on a different tile.
*/
static void			*render_tile(void *arg)
{
	t_thread_data	*thr_data;
	t_color			*tile_px;
	int				tile;
	int				tiles_num;

	thr_data = (t_thread_data *)arg;
	tile = 0;
	tiles_num = (thr_data->e->scr.nx / TILESIZE) * \
		(thr_data->e->scr.ny / TILESIZE);
	while (1)
	{
		tile_px = malloc(sizeof(t_color) * TILESIZE * TILESIZE);
		if (!tile_px)
			break ;
		tile = __sync_add_and_fetch(&thr_data->tile_id, 1) - 1;
		if (tile >= tiles_num)
			break ;
		compute_tile_px(tile, tile_px, thr_data->e);
		pthread_mutex_lock(&thr_data->mutex);
		sync_tile(tile, tile_px, thr_data->e);
		pthread_mutex_unlock(&thr_data->mutex);
		free(tile_px);
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
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(thr[i], NULL);
		i++;
	}
	render_px(e);
	pthread_mutex_destroy(&thr_data.mutex);
	return (1);
}
