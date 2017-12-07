/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_geo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 18:39:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/05 15:50:00 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "cson_parser.h"
#include "ft_printf.h"
#include "geo.h"
#include "light.h"
#include "matrice.h"
#include "rt.h"
#include "utils.h"

void				parse_geo_attributes(char *line, char *v, t_geo *geo)
{
	if (ft_strncmp(line, "\tpos", 4) == 0 && (v += 2))
		vec3_set(atof_cson(&v), atof_cson(&v), atof_cson(&v), geo->origin);
	if (ft_strncmp(line, "\trotation", 9) == 0 && (v += 7))
		geo->rotation = mat3_rot(atof_cson(&v), atof_cson(&v), -atof_cson(&v));
	if (ft_strncmp(line, "\ttranslate", 10) == 0 && (v += 8))
		vec3_trans(vec3_stack(atof_cson(&v), atof_cson(&v), \
			atof_cson(&v)), geo->origin);
	if (ft_strncmp(line, "\tkd", 3) == 0 && (v += 1))
		geo->mater->kd = color_new_stack(atof_cson(&v), atof_cson(&v), \
			atof_cson(&v));
	if (ft_strncmp(line, "\tks", 3) == 0 && (v += 1))
		geo->mater->ks = color_new_stack(atof_cson(&v), \
			atof_cson(&v), atof_cson(&v));
	if (ft_strncmp(line, "\tns", 3) == 0 && (v += 1))
		geo->mater->ns = ft_atof(v);
	if (ft_strncmp(line, "\tillum", 6) == 0 && (v += 4))
		geo->mater->illum = ft_atof(v);
	if (ft_strncmp(line, "\tior", 4) == 0 && (v += 2))
		geo->mater->ior = ft_atof(v);
}

int					add_plane(int *fd, char **line, t_env *e)
{
	char			*value;
	t_geo			*geo;
	t_plane			*plane;

	value = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&plane), sizeof(t_plane), 1, &geo))
		return (5);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		value = *line + 4;
		if (ft_strncmp(*line, "\tnormal", 7) == 0 && (value += 5))
		{
			plane->normal = vec3_stack(atof_cson(&value), \
				atof_cson(&value), atof_cson(&value));
		}
		else if (ft_strncmp(*line, "\tcut_normal", 11) == 0  && (value += 9))
		{
			if (!register_cut(geo, fd, line, value))
				return (12);
		}
		else
			parse_geo_attributes(*line, value, geo);
	}
	if (geo->rotation)
		rotate(&(plane->normal), *geo->rotation);
	add_geometry(geo, &(e->geos));
	return (0);
}

int					add_cone(int *fd, char **line, t_env *e)
{
	char			*value;
	t_geo			*geo;
	t_cone			*cone;

	value = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&cone), sizeof(t_cone), 2, &geo))
		return (6);
	while (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		puts("ORLEANS77");
		if (ft_strncmp(*line, "\tangle", 6) && ft_strncmp(*line, "\taxis", 5) && ft_strncmp(*line, "\tcut_normal", 11))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\tcut_normal", 11) == 0  && (value += 9))
		{
			if (!register_cut(geo, fd, line, value))
				return (12);
				
		}
		else if (ft_strncmp(*line, "\taxis", 5) == 0 && (value += 3))
			cone->axis = vec3_stack(atof_cson(&value), atof_cson(&value),\
				atof_cson(&value));
		else if (ft_strncmp(*line, "\tangle", 6) == 0 && (value += 4))
			cone->angle = ft_atof(value);
	}
	if (geo->rotation)
		rotate(&(cone->axis), *geo->rotation);
	add_geometry(geo, &(e->geos));
	puts("poil");
	return (0);
}

int					add_cylinder(int *fd, char **line, t_env *e)
{
	char			*value;
	t_geo			*geo;
	t_cylinder		*cylinder;

	value = NULL;
	geo = NULL;
	
	if (!malloc_geo((void **)(&cylinder), sizeof(t_cylinder), 3, &geo))
		return (7);
	while (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		
		if (ft_strncmp(*line, "\tradius", 7) && ft_strncmp(*line, "\taxis", 5) && ft_strncmp(*line, "\tcut_normal", 11))
			parse_geo_attributes(*line, value, geo);	
		else if (ft_strncmp(*line, "\tcut_normal", 11) == 0  && (value += 9))
		{
			if (!register_cut(geo, fd, line, value))
				return (12);
		}
		else if (ft_strncmp(*line, "\taxis", 5) == 0 && (value += 3))
			cylinder->axis = vec3_stack(atof_cson(&value), \
				atof_cson(&value), atof_cson(&value));
		else if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			cylinder->radius = ft_atof(value);
	}
	if (geo->rotation)
		rotate(&(cylinder->axis), *geo->rotation);
	add_geometry(geo, &(e->geos));
	print_cut(geo);
	return (0);
}

