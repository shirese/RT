/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_geo2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 18:39:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/28 15:22:35 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "cson_parser.h"
#include "geo.h"
#include "ft_printf.h"
#include "light.h"
#include "matrice.h"
#include "rt.h"
#include "utils.h"

int					add_cube(int *fd, char **line, t_env *e)
{
	char			*v;
	t_geo			*geo;
	t_cube			*cube;

	v = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&cube), sizeof(t_cube), 7, &geo))
		return (11);
	cube->size = 0.0;
	while (get_next_line(*fd, line) && **line == '\t')
	{
		v = *line + 4;
		if (ft_strncmp(*line, "\tdirection", 10) == 0 && (v += 8))
		{
			cube->direction1 = vec3_stack(atof_cson(&v), atof_cson(&v), \
			atof_cson(&v));
		}
		else if (ft_strncmp(*line, "\tsize", 5) == 0 && (v += 3))
			cube->size = ft_atof(v);
		else
			parse_geo_attributes(line, v, geo, fd);
	}
	add_geometry(geo, &(e->geos));
	create_axis(geo);
	return (0);
}
