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
	add_geometry(geo, &(e->geos));
	return (0);
}

int					add_disk(int *fd, char **line, t_env *e)
{
	char			*v;
	t_geo			*geo;
	t_disk			*disk;

	v = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&disk), sizeof(t_disk), 5, &geo))
		return (9);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		v = *line + 4;
		if (ft_strncmp(*line, "\tradius", 7) && ft_strncmp(*line, "\tnormal", 7))
			parse_geo_attributes(*line, v, geo);
		else if (ft_strncmp(*line, "\tradius", 7) == 0 && (v += 5))
			disk->radius = ft_atof(v);
		else if (ft_strncmp(*line, "\tnormal", 7) == 0 && (v += 5))
			disk->normal = vec3_stack(atof_cson(&v), \
				atof_cson(&v), atof_cson(&v));
	}
	if (geo->rotation)
		rotate(&(disk->normal), *geo->rotation);
	add_geometry(geo, &(e->geos));
	return (0);
}
