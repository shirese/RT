/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:12:06 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/13 16:02:57 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <imago2.h>

#include "matrice.h"
#include "rt.h"
#include "vector.h"

t_screen			set_screen(t_win win, t_cam *cam)
{
	t_screen		scr;

	scr.asp_ratio = (double)win.width / (double)win.height;
	scr.scale = tan(deg_to_rad(cam->fov * 0.5));
	scr.nx = win.width;
	scr.ny = win.height;
	scr.low_left_corner = vec3_stack(-2.0, -1.0, -1.0);
	scr.horizontal = vec3_stack(4.0, 0.0, 0.0);
	scr.vertical = vec3_stack(0.0, 2.0, 0.0);
	return (scr);
}

void				free_env(t_env **e)
{
	void			*tmp;

	free((*e)->cam->pos);
	free((*e)->cam->cam_to_world);
	free((*e)->cam);
	while ((*e)->geos)
	{
		tmp = (t_geo *)(*e)->geos;
		free((*e)->geos->curr);
		free((*e)->geos->origin);
		free((*e)->geos->mater);
		(*e)->geos = (*e)->geos->next;
		free(tmp);
	}
	free((*e)->geos);
	while ((*e)->lights)
	{
		tmp = (t_light *)(*e)->lights;
		(*e)->lights = (*e)->lights->next;
		free(((t_light *)tmp)->curr);
		free(((t_light *)tmp)->color);
		free(tmp);
	}
	free((*e)->lights);
	free((*e)->img);
	img_free_pixels((*e)->tex->px);
	free((*e)->tex);
	free(*e);
}

void				init_environment(t_env **e)
{
	*e = malloc(sizeof(t_env));
	(*e)->img = NULL;
	(*e)->win.width = 0;
	(*e)->win.height = 0;
	(*e)->samp_rate = 1;
	(*e)->cam = NULL;
	(*e)->lights = NULL;
	(*e)->geos = NULL;
	(*e)->tex = NULL;
}
