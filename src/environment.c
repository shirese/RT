/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:12:06 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/26 09:57:07 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "matrice.h"
#include "rt.h"
#include "rt_multithread.h"
#include "vector.h"
#include "SDL_stbimage.h"

t_screen			set_screen(t_win win, t_cam *cam)
{
	t_screen		scr;

	scr.asp_ratio = (double)win.w / (double)win.h;
	scr.scale = tan(deg_to_rad(cam->fov * 0.5));
	scr.nx = win.w;
	scr.ny = win.h;
	scr.low_left_corner = vec3_stack(-2.0, -1.0, -1.0);
	scr.horizontal = vec3_stack(4.0, 0.0, 0.0);
	scr.vertical = vec3_stack(0.0, 2.0, 0.0);
	return (scr);
}

static void			free_lights(t_env **e)
{
	t_light			*tmp;

	while ((*e)->lights)
	{
		tmp = (*e)->lights;
		(*e)->lights = (*e)->lights->next;
		if (tmp->type == 2)
			free(((t_directional *)tmp->curr)->dir);
		else if (tmp->type == 3)
			free(((t_point *)tmp->curr)->pos);
		if (tmp->curr)
			free((tmp)->curr);
		free((tmp)->color);
		free(tmp);
	}
	free((*e)->lights);
}
static void			free_geos(t_env **e)
{
	t_geo			*geo;

	geo = NULL;
	while ((*e)->geos)
	{
		geo = (*e)->geos;
		free(geo->curr);
		free(geo->origin);
		free(geo->mater);
		if (geo->tex)
		{
			if (geo->tex->curr)
				SDL_FreeSurface(geo->tex->curr);
			free(geo->tex);
		}
		(*e)->geos = (*e)->geos->next;
		free(geo);
	}
	free((*e)->geos);
}

void				free_env(t_env **e)
{
	if ((*e)->cam)
	{
		free((*e)->cam->pos);
		free((*e)->cam->cam_to_world);
		free((*e)->cam);
	}
	if ((*e)->geos)
		free_geos(e);
	if ((*e)->lights)
		free_lights(e);
	if ((*e)->img)
		free((*e)->img);
	free(*e);
}

void				init_environment(t_env **e)
{
	*e = malloc(sizeof(t_env));
	(*e)->img = NULL;
	(*e)->win.w = 0;
	(*e)->win.h = 0;
	(*e)->samp_rate = 1;
	(*e)->cam = NULL;
	(*e)->lights = NULL;
	(*e)->geos = NULL;
}
