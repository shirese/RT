/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_geo2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 18:39:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/13 10:52:51 by fgallois         ###   ########.fr       */
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

static t_cut					*add_normal_cut(t_geo *geo, char **line, \
char *value, t_vec3 cut_position)
{
	t_vec3						cut_normal;
	t_cut						*new_cut;

	new_cut = NULL;
	if (ft_strncmp(*line, "\tcut_normal", 11) == 0 && (value += 9))
	{
		cut_normal = vec3_stack(atof_cson(&value), atof_cson(&value), \
			atof_cson(&value));
		if (!(new_cut = (t_cut*)ft_realloc((void *)geo->cut, geo->nb_cut \
		* sizeof(t_cut), (geo->nb_cut - 1) * sizeof(t_cut))))
			return (NULL);
		new_cut[geo->nb_cut - 1].cut_position = cut_position;
		new_cut[geo->nb_cut - 1].cut_normal = cut_normal;
	}
	else
		return (NULL);
	return (new_cut);
}

int								register_cut(t_geo *geo, int *fd,\
char **line, char *value)
{
	t_vec3						cut_position;
	t_cut						*new_cut;

	cut_position = vec3_stack(atof_cson(&value), atof_cson(&value), \
	atof_cson(&value));
	geo->nb_cut++;
	if (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		if (!(new_cut = add_normal_cut(geo, line, value, cut_position)))
			return (0);
	}
	else
		return (0);
	geo->cut = new_cut;
	return (1);
}

int								add_sphere(int *fd, char **line, t_env *e)
{
	char						*value;
	t_geo						*geo;
	t_sphere					*sphere;
	int							err;

	value = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&sphere), sizeof(t_sphere), 4, &geo))
		return (8);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		value = *line + 4;
		if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			sphere->radius = ft_atof(value);
		else
		{
			if ((err = parse_geo_attributes(line, value, geo, fd)))
				return (err);
		}
	}
	add_geometry(geo, &(e->geos));
	return (0);
}

int								add_disk(int *fd, char **line, t_env *e)
{
	t_geo						*geo;
	t_disk						*disk;
	char						*value;
	int							err;

	geo = NULL;
	if (!malloc_geo((void **)(&disk), sizeof(t_disk), 5, &geo))
		return (9);
	while (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		if (ft_strncmp(*line, "\tradius", 7) == 0 && (value += 5))
			disk->radius = ft_atof(value);
		else if (ft_strncmp(*line, "\tnormal", 7) == 0 && (value += 5))
			disk->normal = vec3_stack(atof_cson(&value), \
				atof_cson(&value), atof_cson(&value));
		else
		{
			if ((err = parse_geo_attributes(line, value, geo, fd)))
				return (err);
		}
	}
	if (geo->rotation)
		rotate(&(disk->normal), *geo->rotation);
	add_geometry(geo, &(e->geos));
	return (0);
}
