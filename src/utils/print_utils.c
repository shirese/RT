/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:59:47 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/15 16:56:59 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "geo.h"
#include "light.h"
#include "utils.h"

static void			print_lights(t_env *e)
{
	t_light			*light;

	light = e->lights;
	while (light)
	{
		ft_printf("\n\n///		LIGHT		////\n\n");
		ft_printf("TYPE 		[%d]\n", light->type);
		ft_printf("COLOR 		");
		color_print(*light->color);
		if (light->type == 2)
		{
			ft_printf("DIR 		");
			vec3_print(*((t_directional *)light->curr)->dir);
		}
		if (light->type == 3)
		{
			ft_printf("\nPOS 		[%f %f %f]\n", \
				((t_spot *)light->curr)->pos->x,
				((t_spot *)light->curr)->pos->y,
				((t_spot *)light->curr)->pos->z);
		}
		light = light->next;
	}
}

static void			print_geo_mater(t_mater *m)
{
	ft_printf("\nMATER\t\t");
	color_print(m->kd);
	ft_printf("\t\t");
	color_print(m->ks);
	ft_printf("ILLUM\t\t[%d]\nIOR\t\t[%f]\nNS\t\t[%f]\n", m->illum, \
		m->ior, m->ns);
	ft_printf("REFLECTIVITY\t[%f]\n", m->reflectivity);
	ft_printf("TRANSPARENCY\t[%f]\n\n", m->transparency);
}

static void			print_geo2(t_geo *geo)
{
	t_geo		*tmp;
	if (geo->type == 3)
	{
		ft_printf("CYLINDER\nRAD\t\t[%f]\nAXIS\t\t", \
			((t_cylinder *)(geo->curr))->radius);
		vec3_print(((t_cylinder *)(geo->curr))->axis);
	}
	else if (geo->type == 4)
		ft_printf("SPHERE\nRAD\t\t[%f]\n", ((t_sphere *)(geo->curr))->radius);
	else if (geo->type == 5)
	{
		ft_printf("DISK\nRAD\t\t[%f]\nNORMAL\t\t", \
			((t_disk *)(geo->curr))->radius);
		vec3_print(((t_disk *)(geo->curr))->normal);
	}
	else if (geo->type == 6)
	{
		ft_printf("PARABOLOID\nFACTA\t\t[%f]\nFACTB\t\t[%f]\nHEIGHT\t\t[%f]", \
			((t_paraboloid *)(geo->curr))->facta,\
			((t_paraboloid *)(geo->curr))->factb,\
			((t_paraboloid *)(geo->curr))->height);
	}
	else if (geo->type == 7)
	{
		ft_printf("CUBE\nSIZE\t\t[%f]\nDIRECTIONS\n", \
			((t_cube *)(geo->curr))->size);
		vec3_print(((t_cube *)(geo->curr))->direction1);
		vec3_print(((t_cube *)(geo->curr))->direction2);
		vec3_print(((t_cube *)(geo->curr))->direction3);
	}
	else if (geo->type == 8)
	{
		ft_printf("GLASS\nHEIGHT\t\t[%f]\nDIRECTION\n", \
			((t_glass *)(geo->curr))->height);
		vec3_print(((t_glass *)(geo->curr))->direction);
	}		
	if (is_scene_dug(geo))
	{
		tmp = geo;
		ft_printf("NEGATIF OBJECTS :\n");
		while (tmp)
		{
			if (tmp->neg)
			{
				print_geo(tmp->neg);
				ft_printf("\n");
			}
			tmp = tmp->next;
		}
	}
}

void			print_geo(t_geo *geo)
{
	ft_printf("\n\n///		GEO	[%p]	////\n\nORIGIN		", (void *)geo);
	vec3_print(*geo->origin);
	if (geo->rotation && ft_printf("\nROTATION\n\n"))
	{
		vec3_print(geo->rotation->r1);
		vec3_print(geo->rotation->r2);
		vec3_print(geo->rotation->r3);
	}
	print_geo_mater(geo->mater);
	if (geo->type == 1 && ft_printf("PLANE\nNORMAL\t\t"))
		vec3_print(((t_plane *)(geo->curr))->normal);
	else if (geo->type == 2)
	{
		ft_printf("CONE\nANGLE\t\t[%f]\nAXIS\t\t", \
			((t_cone *)(geo->curr))->angle);
		vec3_print(((t_cone *)(geo->curr))->axis);
	}
	else
		print_geo2(geo);
}

void				print_env(t_env *e)
{
	t_geo			*geo;

	ft_printf("\n\n///////////		ENV		///////////\n\n");
	ft_printf("WIN\t\t%d*%d\n", e->win.w, e->win.h);
	ft_printf("SCREEN\t\tRATIO [%f] SCALE [%f]\n", e->scr.asp_ratio, \
		e->scr.scale);
	ft_printf("CAM\t\t");
	vec3_print(*e->cam->pos);
	ft_printf("\nFOV\t\t[%f]\n", e->cam->fov);
	print_lights(e);
	geo = e->geos;
	while (geo)
	{
		print_geo(geo);
		print_cut(geo);
		geo = geo->next;
	}
}
