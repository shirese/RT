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
		return (10);
	para->facta = 0.;
	para->factb = 0.;
	para->height = 0.;
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
			cube->direction1 = vec3_stack(atof_cson(&v), atof_cson(&v), \
			atof_cson(&v));
		else if (ft_strncmp(*line, "\tsize", 5) == 0 && (v += 3))
			cube->size = ft_atof(v);
		else
			parse_geo_attributes(line, v, geo, fd);	
	}
	add_geometry(geo, &(e->geos));
	if (geo->rotation)
		rotate(&(cube->direction1), *geo->rotation);
	create_axis(geo);
	return (0);
}

int					add_glass(int *fd, char **line, t_env *e)
{
	char			*v;
	t_geo			*geo;
	t_glass			*glass;

	v = NULL;
	geo = NULL;
	puts("GENIE");
	if (!malloc_geo((void **)(&glass), sizeof(t_glass), 8, &geo))
		return (12);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		v = *line + 4;
		puts(*line);
	
		if (ft_strncmp(*line, "\tdirection", 10) == 0 && (v += 8))
		{
			vec3_normalize(&glass->direction);
			glass->direction = vec3_stack(atof_cson(&v), atof_cson(&v), \
			atof_cson(&v));
		}
		else if (ft_strncmp(*line, "\theight", 7) == 0 && (v += 5))
			glass->height = ft_atof(v);
		else 
			parse_geo_attributes(line, v, geo, fd);	
	}
	
	if (geo->rotation)
	{
		rotate(&(((t_cylinder*)(glass->cyl)->curr)->axis), *geo->rotation);
		rotate(&(((t_cone*)(glass->cone)->curr)->axis), *geo->rotation);
	}
	set_direction_glass(geo);
	add_geometry(geo, &(e->geos));
	return (0);
}

int				set_direction_glass(t_geo *geo)
{
	t_glass			*glass;
	t_geo			*g;
	t_cylinder		*ess;
	t_cone 			*cone;
	t_sphere		*sphere;

	glass = (t_glass*)geo->curr;
	g = glass->cyl;
	g->origin = vec3_add(*geo->origin, vec3_mult_stack(glass->direction, 0.15));
	g->mater = geo->mater;
	ess = (t_cylinder*)g->curr;
	ess->radius = 0.35;
	ess->axis = glass->direction;
			
	if (!cut_cylinder(g, glass->height))
		return (0);
	g = glass->cone;
	g->origin = vec3_add(*geo->origin, vec3_mult_stack(glass->direction, -0.25));
	//g->mater = geo->mater;
	if (!ft_memcpy((t_mater*)g->mater, (t_mater*)geo->mater, sizeof(geo->mater)))
		return (0);
	g->mater->transparency = 0;
	cone = (t_cone*)g->curr;
	cone->angle = 15.0;
	cone->axis = glass->direction;

	if (!cut_cone(g))
		return (0);
	g = glass->sphere;
	g->origin = vec3_add(*geo->origin, vec3_mult_stack(glass->direction, -0.25));
	//g->mater = geo->mater;
	if (!ft_memcpy((t_mater*)g->mater, (t_mater*)geo->mater, sizeof(geo->mater)))
		return (0);
	g->mater->transparency = 0;
	sphere = (t_sphere*)g->curr;
	sphere->radius = 0.10;
	return (1);
}

int					cut_cylinder(t_geo *cyl, double height)
{
	t_vec3			position;
	t_vec3			normal;
	t_cut			*new_cut;
	t_cylinder		*c;
	t_vec3			*v;
	t_geo			*neg;

	c = (t_cylinder*)cyl->curr;
	new_cut = NULL;
	if (!(new_cut = (t_cut*)malloc(3 * sizeof(t_cut))))
		return (0);
	new_cut[0].cut_position = *cyl->origin;
	new_cut[0].cut_normal = c->axis;

	position = vec3_add_stack(*cyl->origin, vec3_mult_stack(c->axis, height));
	normal = vec3_stack(0.0, -1.0, -0.5);
	//normal = vec3_mult_stack(c->axis, -1.0);
	new_cut[1].cut_position = position;
	new_cut[1].cut_normal = normal;
	cyl->nb_cut = 2;
	cyl->cut = new_cut;

	v = vec3_add(*cyl->origin, vec3_mult_stack(c->axis, height));
	neg = new_sphere(v, 0.8);
	add_geometry_negative(cyl, 0, neg);
	return (1);
}

int					cut_cone(t_geo *cone)
{
	t_vec3			position;
	t_cut			*new_cut;
	t_cone			*c;

	c = (t_cone*)cone->curr;
	new_cut = NULL;
	if (!(new_cut = (t_cut*)malloc(3 * sizeof(t_cut))))
		return (0);
		
	position = vec3_add_stack(*cone->origin, vec3_mult_stack(c->axis, -0.25)); 
	new_cut[0].cut_position = vec3_add_stack(*cone->origin, vec3_mult_stack(c->axis, 0.40));
	new_cut[0].cut_normal = vec3_mult_stack(c->axis, -1.0);

	position = vec3_add_stack(*cone->origin, vec3_mult_stack(c->axis, -0.4)); 
	new_cut[1].cut_position = position;
	new_cut[1].cut_normal = c->axis;
	cone->cut = new_cut;
	cone->nb_cut = 2;
	return (1);
}

