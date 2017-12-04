/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_geo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirese <shirese@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 18:39:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/01 22:09:54 by shirese          ###   ########.fr       */
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
		vec3_set(aton_cson(&v), aton_cson(&v), aton_cson(&v), geo->origin);
	if (ft_strncmp(line, "\trotation", 9) == 0 && (v += 7))
	{
		geo->rotation = mat3_rot(aton_cson(&v), aton_cson(&v), -aton_cson(&v));
	}
	if (ft_strncmp(line, "\ttranslate", 10) == 0 && (v += 8))
	{
		vec3_trans(vec3_stack(aton_cson(&v), aton_cson(&v), \
			aton_cson(&v)), geo->origin);
	}
	if (ft_strncmp(line, "\tkd", 3) == 0 && (v += 1))
	{
		geo->mater->kd = color_new_stack(aton_cson(&v), aton_cson(&v), \
			aton_cson(&v));
	}
	if (ft_strncmp(line, "\tks", 3) == 0 && (v += 1))
	{
		geo->mater->ks = color_new_stack(aton_cson(&v), \
			aton_cson(&v), aton_cson(&v));
	}
	if (ft_strncmp(line, "\tns", 3) == 0 && (v += 1))
		geo->mater->ns = aton_cson(&v);
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
		if (ft_strncmp(*line, "\tn", 2) != 0)
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\tnormal", 7) == 0 && (value += 5))
			plane->normal = vec3_stack(aton_cson(&value), \
				aton_cson(&value), aton_cson(&value));
	}
	geo->type = 1;
	geo->curr = (void *)plane;
	geo->is_hit = g_get_obj_collider(geo->type);
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
		if (ft_strncmp(*line, "\tangle", 6) && ft_strncmp(*line, "\taxis", 5))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\taxis", 5) == 0 && (value += 3))
			cone->axis = vec3_stack(aton_cson(&value), aton_cson(&value),\
				aton_cson(&value));
		else if (ft_strncmp(*line, "\tangle", 6) == 0 && (value += 4))
			cone->angle = ft_atof(value);
	}
	geo->type = 2;
	geo->curr = (void *)cone;
	geo->is_hit = g_get_obj_collider(geo->type);
	if (geo->rotation)
		rotate(&(cone->axis), *geo->rotation);
	add_geometry(geo, &(e->geos));
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
		if (ft_strncmp(*line, "\tradius", 7) && ft_strncmp(*line, "\taxis", 5))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\taxis", 5) == 0 && (value += 3))
			cylinder->axis = vec3_stack(aton_cson(&value), \
				aton_cson(&value), aton_cson(&value));
		else if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			cylinder->radius = ft_atof(value);
	}
	geo->type = 3;
	geo->curr = (void *)cylinder;
	geo->is_hit = g_get_obj_collider(geo->type);
	if (geo->rotation)
		rotate(&(cylinder->axis), *geo->rotation);
	add_geometry(geo, &(e->geos));
	return (0);
}

int					add_sphere(int *fd, char **line, t_env *e)
{
	char			*value;
	t_geo			*geo;
	t_sphere		*sphere;

	value = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&sphere), sizeof(t_sphere), 4, &geo))
		return (8);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		value = *line + 4;
		if (ft_strncmp(*line, "\tradius", 7) != 0)
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			sphere->radius = ft_atof(value);
	}
	geo->type = 4;
	geo->curr = (void *)sphere;
	geo->is_hit = g_get_obj_collider(geo->type);
	add_geometry(geo, &(e->geos));
	return (0);
}

int					add_disk(int *fd, char **line, t_env *e)
{
	char			*value;
	t_geo			*geo;
	t_disk			*disk;

	value = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&disk), sizeof(t_disk), 5, &geo))
		return (9);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		value = *line + 4;
		if (ft_strncmp(*line, "\tradius", 7) && ft_strncmp(*line, "\tnormal", 7))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			disk->radius = ft_atof(value);
		else if (ft_strncmp(*line, "\tnormal", 7) == 0 && (value += 5))
		{
			disk->normal = vec3_stack(aton_cson(&value), \
			aton_cson(&value), aton_cson(&value));
		}
	}
	geo->type = 5;
	geo->curr = (void *)disk;
	geo->is_hit = g_get_obj_collider(geo->type);
	if (geo->rotation)
		rotate(&(disk->normal), *geo->rotation);
	add_geometry(geo, &(e->geos));
	return (0);
}


int					add_parahyp(int *fd, char **line, t_env *e)
{
	char			*value;
	t_geo			*geo;
	t_parahyp			*ph;

	value = NULL;
	geo = NULL;
	
	if (!malloc_geo((void **)(&ph), sizeof(t_parahyp), 7, &geo))
		return (11);
	while (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		if (ft_strncmp(*line, "\tfacta", 4) && ft_strncmp(*line, "\tfactb", 4) && \
		ft_strncmp(*line, "\theight", 7))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\tfacta", 6) == 0 && (value += 4))
			ph->facta = ft_atof(value);
		else if (ft_strncmp(*line, "\tfactb", 6) == 0 && (value += 4))
			ph->factb = ft_atof(value);
		else if (ft_strncmp(*line, "\theight", 7) == 0 && (value += 5))
			ph->height = ft_atof(value);
	}
	geo->type = 7;
	geo->curr = (void *)ph;
	geo->is_hit = g_get_obj_collider(geo->type);
	//if (geo->rotation)
		//rotate(&(parahyp->axis), *geo->rotation);
	add_geometry(geo, &(e->geos));
	return (0);
}
