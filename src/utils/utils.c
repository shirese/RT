/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:16:21 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/08 10:48:16 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "light.h"
#include "geo.h"
#include "rt.h"
#include "vector.h"

static void			atof_cson_norme(int d, double *f, double *r, char **str)
{
	if (d)
		*f /= 10.0f;
	*r = *r * 10.0f + (double)(**str - '0');
}

double				atof_cson(char **str)
{
	double			rez;
	double			fact;
	int				dot_seen;

	rez = 0;
	fact = 1;
	dot_seen = 0;
	while (**str == ' ')
		(*str)++;
	if (**str == '-' && ((*str)++))
		fact = -1;
	else if (**str == '+' && ((*str)++))
		fact = 1;
	while ((ft_isdigit(**str) || **str == '.') && **str != '\0')
	{
		if (dot_seen == 0 && **str == '.')
			dot_seen = 1;
		else if (ft_isdigit(**str))
			atof_cson_norme(dot_seen, &fact, &rez, str);
		(*str)++;
	}
	(*str) += 2;
	return (rez * fact);
}

static void			print_light(t_light *light)
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
		ft_printf("\nPOS 		[%f %f %f]\n", ((t_spot *)light->curr)->pos->x,
			((t_spot *)light->curr)->pos->y,
			((t_spot *)light->curr)->pos->z);
	}
}

static void			print_geo_mater(t_mater *m)
{
	ft_printf("\nMATER\t\t");
	color_print(m->kd);
	ft_printf("\t\t");
	color_print(m->ks);
	ft_printf("ILLUM\t\t[%d]\nIOR\t\t[%f]\nNS\t\t[%f]\n", m->illum, m->ior, m->ns);
	ft_printf("\n");
}

static void			print_geo(t_geo *geo)
{
	ft_printf("\n\n///		GEO	[%p]	////\n\nORIGIN		", (void *)geo);
	vec3_print(*geo->origin);
	if (geo->rotation && ft_printf("\nROTATION	"))
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
		ft_printf("CONE\nANGLE	[%f]\nAXIS\t\t", ((t_cone *)(geo->curr))->angle);
		vec3_print(((t_cone *)(geo->curr))->axis);
	}
	else if (geo->type == 3)
	{
		ft_printf("CYLINDER\nRAD\t\t[%f]\nAXIS\t\t", \
			((t_cylinder *)(geo->curr))->radius);
		vec3_print(((t_cylinder *)(geo->curr))->axis);
	}
	else if (geo->type == 4)
		ft_printf("SPHERE\nRAD\t\t[%f]\n", ((t_sphere *)(geo->curr))->radius);
	else if (geo->type == 5)
	{
		ft_printf("DISK\nRAD\t\t[%f]\nNORMAL\t\t", ((t_disk *)(geo->curr))->radius);
		vec3_print(((t_disk *)(geo->curr))->normal);
	}
}

void				print_env(t_env *e)
{
	t_light			*light;
	t_geo			*geo;

	ft_printf("\n\n///////////		ENV		///////////\n\n");
	ft_printf("WIN\t\t%d*%d\n", e->win.width, e->win.height);
	ft_printf("SCREEN\t\tRATIO [%f] SCALE [%f]\n", e->scr.asp_ratio, \
		e->scr.scale);
	ft_printf("CAM\t\t");
	vec3_print(*e->cam->pos);
	ft_printf("\nFOV\t\t[%f]\n", e->cam->fov);
	light = e->lights;
	while (light)
	{
		print_light(light);
		light = light->next;
	}
	geo = e->geos;
	while (geo)
	{
		print_geo(geo);
		geo = geo->next;
	}
}
