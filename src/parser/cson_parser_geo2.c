/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_geo2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 18:39:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/14 13:49:00 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "cson_parser.h"
#include "ft_printf.h"
#include "geo.h"
#include "ft_printf.h"
#include "light.h"
#include "matrice.h"
#include "rt.h"
#include "utils.h"

static t_cut		*add_normal_cut(t_geo *geo, char **line, char *v, \
	t_vec3 cut_position)
{
	t_vec3			cut_normal;
	t_cut			*new_cut;

	new_cut = NULL;
	if (ft_strncmp(*line, "\tcut_normal", 11) == 0 && (v += 9))
	{
		cut_normal = vec3_stack(atof_cson(&v), atof_cson(&v), \
			atof_cson(&v));
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

int					register_cut(t_geo *geo, int *fd, char **line, char *v)
{
	t_vec3			cut_position;
	t_cut			*new_cut;

	cut_position = vec3_stack(atof_cson(&v), atof_cson(&v), \
	atof_cson(&v));
	if (get_next_line(*fd, line) && **line == '\t' && (v = *line + 4))
	{
		geo->nb_cut++;
		if (!(new_cut = add_normal_cut(geo, line, v, cut_position)))
		{
			geo->nb_cut--;
			return (0);
		}
		geo->cut = new_cut;
		return (1);
	}
	return (0);
}

int					add_sphere(int *fd, char **line, t_env *e)
{
	char			*v;
	t_geo			*geo;
	t_sphere		*sphere;

	v = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&sphere), sizeof(t_sphere), 4, &geo))
		return (8);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		v = *line + 4;
		if (ft_strncmp(*line, "\tradius", 7) == 0 && (v += 5))
			sphere->radius = ft_atof(v);
		else
			parse_geo_attributes(line, v, geo, fd);
	}
	add_geometry(geo, &(e->geos));
	return (0);
}

int					add_disk(int *fd, char **line, t_env *e)
{
	t_geo			*geo;
	t_disk			*disk;
	char			*v;

	geo = NULL;
	v = NULL;
	if (!malloc_geo((void **)(&disk), sizeof(t_disk), 5, &geo))
		return (9);
	disk->radius = 0;
	while (get_next_line(*fd, line) && **line == '\t' && (v = *line + 4))
	{
		if (ft_strncmp(*line, "\tradius", 7) == 0 && (v += 5))
			disk->radius = ft_atof(v);
		else if (ft_strncmp(*line, "\tnormal", 7) == 0 && (v += 5))
			disk->normal = vec3_stack(atof_cson(&v), \
				atof_cson(&v), atof_cson(&v));
		else
			parse_geo_attributes(line, v, geo, fd);
	}
	if (geo->rotation)
		rotate(&(disk->normal), *geo->rotation);
	add_geometry(geo, &(e->geos));
	return (0);
}

int					add_paraboloid(int *fd, char **line, t_env *e)
{
	char			*v;
	t_geo			*geo;
	t_paraboloid	*para;

	v = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&para), sizeof(t_paraboloid), 6, &geo))
		return (6);
	para->facta = 1.;
	para->factb = 1.;
	para->height = 1.;
	while (get_next_line(*fd, line) && **line == '\t' && (v = *line + 4))
	{
		if (ft_strncmp(*line, "\tfacta", 6) == 0 && (v += 4))
			para->facta = ft_atof(v);
		if (ft_strncmp(*line, "\tfactb", 6) == 0 && (v += 4))
			para->factb = ft_atof(v);
		if (ft_strncmp(*line, "\theight", 7) == 0 && (v += 5))
			para->height = ft_atof(v);
		else
			parse_geo_attributes(line, v, geo, fd);
	}
	add_geometry(geo, &(e->geos));
	return (0);
}
