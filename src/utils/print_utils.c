/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:59:47 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/09 10:45:08 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "geo.h"
#include "light.h"
#include "utils.h"

void				print_geo_mater(t_mater *m)
{
	ft_putstr("\nMATER\t\t");
	print_color(m->kd);
	ft_putstr("\t\t");
	print_color(m->ks);
	ft_printf("ILLUM\t\t[%d]\nIOR\t\t[%f]\nNS\t\t[%f]\n", m->illum, \
		m->ior, m->ns);
	ft_printf("REFLECTIVITY\t[%f]\n", m->reflectivity);
	ft_printf("TRANSPARENCY\t[%f]\n\n", m->transparency);
}

static void			print_geo2(t_geo *geo)
{
	if (geo->type == 6)
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
		ft_printf("GLASS\nH\t\t[%f]\nDIR\n", ((t_glass *)(geo->curr))->height);
		vec3_print(((t_glass *)(geo->curr))->direction);
		print_geo((t_geo*)((t_glass *)(geo->curr))->cyl);
		print_cut((t_geo*)((t_glass *)(geo->curr))->cyl);
		print_geo((t_geo*)((t_glass *)(geo->curr))->cone);
		print_cut((t_geo*)((t_glass *)(geo->curr))->cone);
		print_geo((t_geo*)((t_glass *)(geo->curr))->sphere);
	}
}

static void			print_geos(t_geo *geo)
{
	if (geo->type == 1 && ft_printf("PLANE\nNORMAL\t\t"))
		vec3_print(((t_plane *)(geo->curr))->normal);
	else if (geo->type == 2)
	{
		ft_printf("CONE\nANGLE\t\t[%f]\nAXIS\t\t", \
			((t_cone *)(geo->curr))->angle);
		vec3_print(((t_cone *)(geo->curr))->axis);
	}
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
	else
		print_geo2(geo);
}

void				print_negative_geos(t_geo *geo)
{
	t_geo			*tmp;

	if (is_scene_dug(geo))
	{
		tmp = geo;
		ft_putendl("NEGATIVE OBJECTS :");
		while (tmp)
		{
			if (tmp->neg)
			{
				print_geo(tmp->neg);
				ft_putchar('\n');
			}
			tmp = tmp->next;
		}
	}
}

void				print_geo(t_geo *geo)
{
	ft_printf("\n\n///\t\tGEO [%p]\t\t////\n\nORIGIN\t\t", (void *)geo);
	vec3_print(*geo->origin);
	if (geo->rotation)
	{
		ft_putstr("\nROTATION\n\n");
		ft_putchar('\t');
		vec3_print(geo->rotation->r1);
		ft_putchar('\t');
		vec3_print(geo->rotation->r2);
		ft_putchar('\t');
		vec3_print(geo->rotation->r3);
	}
	ft_printf("\nSHADER\t\t[%d]", geo->shader_type);
	print_geo_mater(geo->mater);
	print_geos(geo);
	print_negative_geos(geo);
}
