/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 10:19:11 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 16:47:43 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rt.h"
#include "vector.h"

t_cone					*new_cone(t_geo *g, t_vec3 *position, t_vec3 axis, double angle)
{
	t_cone 			*cone;
	t_geo			*geo;

	geo = NULL;
	if (!malloc_geo((void **)(&cone), sizeof(t_cone), 2, &geo))
		return (0);
	*geo->origin = *position;
	cone = (t_cone*)geo->curr;
	cone->axis = axis;
	cone->angle = angle * M_PI / 180;
	return (cone);
}


int					belong_to_cone(t_geo *geo, t_vec3 pos)
{
	t_cone			*c;
	t_vec3			diff;
	t_vec3			proj;
	t_vec3			dif;
	t_vec3			oh;

	c = (t_cone*)geo->curr;
	diff = vec3_sub_stack(*geo->origin, pos);
	proj = vec3_add_stack(c->axis, \
		vec3_mult_stack(*geo->origin, vec3_dot(diff, c->axis)));
	dif = vec3_sub_stack(proj, pos);
	oh = vec3_sub_stack(proj, *geo->origin);
	if (vec3_norm(dif) <= tan(c->angle) * vec3_norm(oh))
		return (1);
	return (0);
}
