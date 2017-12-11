/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_geo2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 18:39:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 18:05:27 by chaueur          ###   ########.fr       */
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

int					add_disk(int *fd, char **line, t_env *e)
{
	char			*v;
	t_geo			*geo;
	t_disk			*disk;

	v = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&disk), sizeof(t_disk), 5, &geo))
		return (9);
	disk->radius = 0;
	while (get_next_line(*fd, line) && **line == '\t')
	{
		v = *line + 4;
		if (ft_strncmp(*line, "\tradius", 7) && \
			ft_strncmp(*line, "\tnormal", 7))
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

int					add_paraboloid(int *fd, char **line, t_env *e)
{
	char			*value;
	t_geo			*geo;
	t_paraboloid	*para;

	value = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&para), sizeof(t_paraboloid), 6, &geo))
		return (10);
	para->facta = 0.;
	para->factb = 0.;
	para->height = 0.;
	while (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		if (ft_strncmp(*line, "\tfacta", 5) && ft_strncmp(*line, "\tfactb", 5)\
				&& ft_strncmp(*line, "\theight", 7))
			parse_geo_attributes(*line, value, geo);
		else if (ft_strncmp(*line, "\tfacta", 6) == 0 && (value += 4))
			para->facta = ft_atof(value);
		else if (ft_strncmp(*line, "\tfactb", 6) == 0 && (value += 4))
			para->factb = ft_atof(value);
		else if (ft_strncmp(*line, "\theight", 7) == 0 && (value += 5))
			para->height = ft_atof(value);
	}
	add_geometry(geo, &(e->geos));
	return (0);
}
