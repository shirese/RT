/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 12:06:59 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/28 15:30:21 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rt.h"

t_vec3			get_norm(t_geo *geo, t_hp hp)
{
	if (geo->type == 1)
		return (plane_norm(geo));
	else if (geo->type == 2)
		return (cone_norm(geo, hp.p));
	else if (geo->type == 3)
		return (cylinder_norm(geo, hp));
	else if (geo->type == 4)
		return (sphere_norm(geo, hp.p));
	else if (geo->type == 5)
		return (disk_norm(geo));
	else if (geo->type == 6)
		return (para_norm(geo, hp.p));
	else if (geo->type == 7)
		return (cube_norm(geo, hp));
	else if (geo->type == 8)
		return (glass_norm(geo, hp));
	return (vec3_stack(0.0, 0.0, 0.0));
}

int					belong_to(t_geo *g, t_vec3 pos)
{
	if (g->type == 1)
		return (belong_to_plane(g, pos));
	else if (g->type == 2)
		return (belong_to_cone(g, pos));
	else if (g->type == 3)
		return (belong_to_cylinder(g, pos));
	else if (g->type == 4)
		return (belong_to_sphere(g, pos));
	else if (g->type == 5)
		return (belong_to_disk(g, pos));
	else if (g->type == 6)
		return (belong_to_paraboloid(g, pos));
	else if (g->type == 7)
		return (belong_to_cube(g, pos));
	else if (g->type == 8)
		return (belong_to_glass(g, pos));
	return (0);
}
