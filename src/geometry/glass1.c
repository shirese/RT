/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/09 15:15:27 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"
#include "ft_printf.h"

static int			set_glass_cylinder(t_glass **glass, t_geo *geo)
{
	t_cylinder		*cyl;
	t_geo			*geo_cyl;

	geo_cyl = (*glass)->cyl;
	*geo_cyl->origin = vec3_add_stack(*geo->origin, \
		vec3_mult_stack((*glass)->direction, 0.15));
	ft_memcpy(geo_cyl->mater, geo->mater, sizeof(t_mater));
	cyl = geo_cyl->curr;
	cyl->radius = 0.35;
	cyl->axis = (*glass)->direction;
	if (!cut_cylinder_in_glass(geo_cyl, (*glass)->height))
		return (0);
	return (1);
}

static int			set_glass_cone(t_glass **glass, t_geo *geo)
{
	t_cone			*cone;
	t_geo			*geo_cone;

	geo_cone = (*glass)->cone;
	*geo_cone->origin = vec3_add_stack(*geo->origin, \
	vec3_mult_stack((*glass)->direction, -0.25));
	ft_memcpy(geo_cone->mater, geo->mater, sizeof(t_mater));
	cone = geo_cone->curr;
	cone->angle = 15.0;
	cone->axis = (*glass)->direction;
	if (!cut_cone_in_glass(geo_cone))
		return (0);
	return (1);
}

static int			set_glass_sphere(t_glass **glass, t_geo *geo)
{
	t_sphere		*sphere;
	t_geo			*geo_sphere;

	geo_sphere = (*glass)->sphere;
	*geo_sphere->origin = vec3_add_stack(*geo->origin, \
	vec3_mult_stack((*glass)->direction, -0.25));
	ft_memcpy(geo_sphere->mater, geo->mater, sizeof(t_mater));
	geo_sphere->mater->transparency = 0;
	sphere = geo_sphere->curr;
	sphere->radius = 0.10;
	return (1);
}

int					setup_glass(t_env *e, t_geo *geo, t_glass *glass)
{
	if (geo->rotation)
	{
		rotate(&(((t_cylinder*)(glass->cyl)->curr)->axis), *geo->rotation);
		rotate(&(((t_cone*)(glass->cone)->curr)->axis), *geo->rotation);
	}
	if (!set_glass_cylinder(&glass, geo) || !set_glass_cone(&glass, geo) \
		|| !set_glass_sphere(&glass, geo))
	{
		free_geo_glass(glass);
		return (12);
	}
	add_geometry(geo, &(e->geos));
	return (0);
}

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
	return (setup_glass(e, geo, glass));
}
