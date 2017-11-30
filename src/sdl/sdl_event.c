/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirese <shirese@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:41:29 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/30 21:53:38 by shirese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "rt.h"
#include "rt_multithread.h"

static void			sdl_save_img_norme(unsigned char *px, SDL_Surface *info_surface)
{
	SDL_Surface		*save_surface;

	save_surface = SDL_CreateRGBSurfaceFrom(px, info_surface->w, \
		info_surface->h, info_surface->format->BitsPerPixel, \
		info_surface->w * info_surface->format->BytesPerPixel, \
		info_surface->format->Rmask, info_surface->format->Gmask, \
		info_surface->format->Bmask, info_surface->format->Amask);
	if (save_surface == NULL)
	{
		ft_printf("SDL_CreateRGBSurfaceFrom failed: %s\n", SDL_GetError());
		free(px);
		return ;
	}
	SDL_SaveBMP(save_surface, "saves/save.bmp");
	free(px);
	SDL_FreeSurface(save_surface);
}

static void			sdl_save_img(t_env *e)
{
	SDL_Surface		*info_surface;
	int				w;
	int				h;
	unsigned char	*pixels;

	if (!(info_surface = SDL_GetWindowSurface(e->win.handle)))
	{
		ft_printf("SDL_GetWindowSurface failed: %s\n", SDL_GetError());
		return ;
	}
	pixels = malloc(sizeof(unsigned char) * info_surface->w * info_surface->h \
		* info_surface->format->BytesPerPixel);
	if (SDL_RenderReadPixels(e->win.rend, &info_surface->clip_rect, info_surface->format->format, pixels, info_surface->w * info_surface->format->BytesPerPixel) != 0)
	{
		ft_printf("SDL_RenderReadPixels failed: %s\n", SDL_GetError());
		free(pixels);
		return ;
	}
	sdl_save_img_norme(pixels, info_surface);
}

static int			check_trans_event(SDL_Keycode k, t_env *e)
{
	int				trans;

	trans = 0;
	if (k == SDLK_DOWN && (trans = 1))
		e->geos->origin->y -= 0.01;
	if (k == SDLK_UP && (trans = 1))
		e->geos->origin->y += 0.01;
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
}
