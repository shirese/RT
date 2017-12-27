/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_drag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 10:12:51 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/27 11:57:00 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rt.h"

void				release_virtual_plane(t_geo **virtual_plane)
{
	if (*virtual_plane)
	{
		free((*virtual_plane)->origin);
		if ((*virtual_plane)->curr)
			free((*virtual_plane)->curr);
		free(*virtual_plane);
	}
}

int					setup_virtual_plane(t_geo **virtual_plane)
{
	*virtual_plane = malloc(sizeof(t_geo));
	if (!*virtual_plane)
		return (0);
	(*virtual_plane)->type = 1;
	(*virtual_plane)->origin = vec3_new(0, 0, 0);
	(*virtual_plane)->cut = NULL;
	(*virtual_plane)->nb_cut = 0;
	(*virtual_plane)->neg = NULL;
	(*virtual_plane)->borns_neg = NULL;
	(*virtual_plane)->curr = malloc(sizeof(t_plane));
	if (!(*virtual_plane)->curr)
	{
		free((*virtual_plane)->origin);
		free(*virtual_plane);
		return (0);
	}
	((t_plane *)(*virtual_plane)->curr)->normal = vec3_stack(0., 0., 1.);
	return (1);
}

static int			check_drag_motion(t_geo **v_plane, t_geo **geo, \
	SDL_Event event, t_env *e)
{
	t_hp			hp;
	t_ray			r;

	if (event.type == SDL_MOUSEMOTION)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			r = init_ray(gen_ray_origin(*e->cam->cam_to_world, *e->cam->pos), \
			gen_ray_direction(event.motion.x, event.motion.y, e), 1, 1.0);
			hp = hit_plane(*v_plane, &r);
			*(*geo)->origin = hp.p;
			return (1);
		}
	}
	else if ((*geo) && event.type == SDL_MOUSEWHEEL)
	{
		(*geo)->origin->z += ((1 - 2 * (event.wheel.y + 0.5) / e->scr.ny) * \
				e->scr.scale * 1 / e->scr.asp_ratio) / 10.;
		(*v_plane)->origin->z = (*geo)->origin->z;
		return (1);
	}
	return (0);
}

int					check_drag_event(SDL_Event ev, t_env *e)
{
	static int		onclick;
	static t_geo	*geo;
	static t_geo	*v_plane;
	t_hp			hp;
	t_ray			r;

	if (ev.type == SDL_MOUSEBUTTONUP)
	{
		onclick = 0;
		if (v_plane)
			release_virtual_plane(&v_plane);
	}
	else if (ev.type == SDL_MOUSEBUTTONDOWN)
	{
		r = init_ray(gen_ray_origin(*e->cam->cam_to_world, *e->cam->pos), \
		gen_ray_direction(ev.motion.x, ev.motion.y, e), 1, 1.0);
		geo = ray_hit(&r, &hp, NULL, e);
		onclick = 1;
		if (geo && setup_virtual_plane(&v_plane))
			vec3_set(geo->origin->x, geo->origin->y, geo->origin->z, \
				v_plane->origin);
	}
	if (geo && onclick)
		return (check_drag_motion(&v_plane, &geo, ev, e));
	return (0);
}
