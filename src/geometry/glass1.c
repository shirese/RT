/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/28 15:42:02 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"
#include "ft_printf.h"

int					add_glass(int *fd, char **line, t_env *e)
{
	char			*v;
	t_geo			*geo;
	t_glass			*glass;

	v = NULL;
	geo = NULL;
	if (!malloc_geo((void **)(&glass), sizeof(t_glass), 8, &geo))
		return (12);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		v = *line + 4;
		if (ft_strncmp(*line, "\tdirection", 10) == 0 && (v += 8))
		{
			glass->direction = vec3_stack(atof_cson(&v), atof_cson(&v), \
			atof_cson(&v));
			vec3_normalize(&glass->direction);
		}
		else if (ft_strncmp(*line, "\theight", 7) == 0 && (v += 5))
			glass->height = ft_atof(v);
		else 
			parse_geo_attributes(line, v, geo, fd);	
	}
	return (modif_glass(e, geo, glass));
}

static int			set_cylinder_of_glass(t_geo *geo)
{
	t_cylinder		*cyl;
	t_geo			*g;
	t_glass			*glass;

	glass = (t_glass*)geo->curr;
	g = glass->cyl;
	g->origin = vec3_add(*geo->origin, vec3_mult_stack(glass->direction, 0.15));
	g->mater = geo->mater;
	cyl = (t_cylinder*)g->curr;
	cyl->radius = 0.35;
	cyl->axis = glass->direction;
	if (!cut_cylinder_in_glass(g, glass->height))
		return (0);
	return (1);
}

static int			set_cone_of_glass(t_geo *geo)
{
	t_glass			*glass;
	t_geo			*g;
	t_cone			*cone;

	glass = (t_glass*)geo->curr;
	g = glass->cyl;
	if (!set_cylinder_of_glass(geo))
		return (0);
	g = glass->cone;
	g->origin = vec3_add(*geo->origin, vec3_mult_stack(glass->direction, -0.25));
	if (!ft_memcpy((t_mater*)g->mater, (t_mater*)geo->mater, sizeof(geo->mater)))
		return (0);
	g->mater->transparency = 0;
	cone = (t_cone*)g->curr;
	cone->angle = 15.0;
	cone->axis = glass->direction;
	if (!cut_cone_in_glass(g))
		return (0);
	return (1);
}

static int			set_sphere_of_glass(t_geo *geo)
{
	t_glass			*glass;
	t_geo			*g;
	t_sphere		*sphere;

	glass = (t_glass*)geo->curr;
	g = glass->sphere;
	sphere = (t_sphere*)g->curr;
	g->origin = vec3_add(*geo->origin, vec3_mult_stack(glass->direction, -0.25));
	if (!ft_memcpy((t_mater*)g->mater, (t_mater*)geo->mater, sizeof(geo->mater)))
		return (0);
	g->mater->transparency = 0;
	sphere = (t_sphere*)g->curr;
	sphere->radius = 0.10;
	return (1);
}

int				set_direction_glass(t_geo *geo)
{
	if (!set_cylinder_of_glass(geo) || !set_cone_of_glass(geo) || \
	!set_sphere_of_glass(geo))
		return (0);
	return (1);
}
