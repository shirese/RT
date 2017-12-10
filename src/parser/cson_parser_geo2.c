/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_geo2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 18:39:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/05 13:00:21 by chaueur          ###   ########.fr       */
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

int					register_cut(t_geo *geo, int *fd, char **line, char *value)
{
	t_vec3		cut_normal;
	t_vec3		cut_position;
	t_cut		*new_cut;

	cut_normal = vec3_stack(atof_cson(&value), atof_cson(&value), \
	atof_cson(&value));
	geo->nb_cut++;
	if (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		if (ft_strncmp(*line, "\tcut_position", 13) == 0 && (value += 11))
		{
			cut_position = vec3_stack(atof_cson(&value), atof_cson(&value), \
				atof_cson(&value));
			if (!(new_cut = (t_cut*)ft_realloc((void *)geo->cut, geo->nb_cut * sizeof(t_cut), (geo->nb_cut - 1) * sizeof(t_cut))))
				return (0);
			new_cut[geo->nb_cut - 1].cut_normal = cut_normal;
			new_cut[geo->nb_cut - 1].cut_position = cut_position;
		}
		else
			return (0);
	}
	else
		return (0);
	geo->cut = new_cut;
	return (1);
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
		if (ft_strncmp(*line, "\tradius", 7) != 0 && ft_strncmp(*line, "\tcut_normal", 11))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\tcut_normal", 11) == 0  && (value += 9))
		{
			if (!register_cut(geo, fd, line, value))
				return (12);
		}
		else if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			sphere->radius = ft_atof(value);
	}
	add_geometry(geo, &(e->geos));
	return (0);
}

int					add_disk(int *fd, char **line, t_env *e)
{
	char			*v;
	t_geo			*geo;
	t_disk			*disk;
	char 			*value;

	v = NULL;
	geo = NULL;
	value = NULL;
	
	if (!malloc_geo((void **)(&disk), sizeof(t_disk), 5, &geo))
		return (9);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		value = *line + 4;
		if (ft_strncmp(*line, "\tradius", 7) && ft_strncmp(*line, "\tnormal", 7) && ft_strncmp(*line, "\tcut_normal", 11))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\tcut_normal", 11) == 0  && (value += 9))
		{
			if (!register_cut(geo, fd, line, value))
				return (12);
		}
		else if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			disk->radius = ft_atof(value);
		else if (ft_strncmp(*line, "\tnormal", 7) == 0 && (value += 5))
			disk->normal = vec3_stack(atof_cson(&value), \
				atof_cson(&value), atof_cson(&value));
	}
	
	if (geo->rotation)
		rotate(&(disk->normal), *geo->rotation);
	add_geometry(geo, &(e->geos));
	
	return (0);
}
