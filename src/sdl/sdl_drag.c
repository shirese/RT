/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_drag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 10:12:51 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/11 15:09:49 by chaueur          ###   ########.fr       */
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

static int			check_drag_motion(t_geo **v_p, t_geo **geo, \
	SDL_Event event, t_env *e)
{
	t_hp			hp;
	t_ray			r;

	if (event.type == SDL_MOUSEMOTION)
	{
		r = init_ray(gen_ray_origin(*e->cam->cam_to_world, *e->cam->pos), \
		gen_ray_direction(event.motion.x, event.motion.y, e), 1, 1.0);
		hp = hit_plane(*v_p, &r);
		*(*geo)->origin = hp.p;
		return (1);
	}
	if ((*geo) && event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y > 0 && (*geo)->origin->z > e->cam->pos->z - 0.2)
			return (0);
		(*geo)->origin->z += (double)event.wheel.y * 0.005;
		(*v_p)->origin->z = (*geo)->origin->z;
		return (1);
	}
	return (0);
}

static void			check_mouse_geo(t_geo **p, t_geo **geo, \
SDL_Event ev, t_env *e)
{
	t_ray			r;
	t_hp			hp;

	r = init_ray(gen_ray_origin(*e->cam->cam_to_world, *e->cam->pos), \
	gen_ray_direction(ev.button.x, ev.button.y, e), 1, 1.0);
	*geo = ray_hit(&r, &hp, NULL, e);
	if (*geo && setup_virtual_plane(p))
		vec3_set((*geo)->origin->x, (*geo)->origin->y, (*geo)->origin->z, \
			(*p)->origin);
}

int					check_drag_event(SDL_Event ev, t_env *e)
{
	static int		onclick;
	static t_geo	*geo;
	static t_geo	*v_plane;

	if (ev.type == SDL_MOUSEBUTTONUP)
	{
		onclick = 0;
		if (!onclick && geo && v_plane)
		{
			geo = NULL;
			release_virtual_plane(&v_plane);
			v_plane = NULL;
		}
	}
	if (!v_plane && !geo && ev.type == SDL_MOUSEBUTTONDOWN)
	{
		onclick = 1;
		check_mouse_geo(&v_plane, &geo, ev, e);
	}
	if (v_plane && geo && onclick)
		return (check_drag_motion(&v_plane, &geo, ev, e));
	return (0);
}
