/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_geo2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 18:39:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/08 17:46:17 by chaueur          ###   ########.fr       */
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
			disk->normal = vec3_stack(ft_atof_cson(&value), \
			ft_atof_cson(&value), ft_atof_cson(&value));
			//ft_putnbr(disk->normal.z);
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

int					add_pipe(int *fd, char **line, t_env *e)
{
	char			*value;
	t_geo			*geo;
	t_pipe			*pipe;

	value = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&pipe), sizeof(t_pipe), 6, &geo))
		return (10);
	while (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		if (ft_strncmp(*line, "\tradius", 7) && ft_strncmp(*line, "\taxis", 5) && \
		ft_strncmp(*line, "\theight", 7))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\taxis", 5) == 0 && (value += 3))
			pipe->axis = vec3_stack(ft_atof_cson(&value), \
				ft_atof_cson(&value), ft_atof_cson(&value));
		else if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			pipe->radius = ft_atof(value);
		else if (ft_strncmp(*line, "\theight", 7) == 0 && (value += 5))
			pipe->height = ft_atof(value);
	}
	geo->type = 6;
	geo->curr = (void *)pipe;
	geo->is_hit = g_get_obj_collider(geo->type);
	if (geo->rotation)
		rotate(&(pipe->axis), *geo->rotation);
	add_geometry(geo, &(e->geos));
	return (0);
}
