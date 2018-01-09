/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/09 15:13:32 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int						cut_cylinder_in_glass(t_geo *cyl, double height)
{
	t_vec3			position;
	t_vec3			normal;
	t_cut			*new_cut;
	t_cylinder		*c;

	c = (t_cylinder*)cyl->curr;
	new_cut = NULL;
	if (!(new_cut = (t_cut*)malloc(3 * sizeof(t_cut))))
		return (0);
	new_cut[0].cut_position = *cyl->origin;
	new_cut[0].cut_normal = c->axis;
	position = vec3_add_stack(*cyl->origin, vec3_mult_stack(c->axis, height));
	normal = vec3_mult_stack(c->axis, -1.0);
	new_cut[1].cut_position = position;
	new_cut[1].cut_normal = normal;
	cyl->nb_cut = 2;
	cyl->cut = new_cut;
	return (1);
}

int						cut_cone_in_glass(t_geo *cone)
{
	t_vec3			position;
	t_cut			*new_cut;
	t_cone			*c;

	c = (t_cone*)cone->curr;
	new_cut = NULL;
	if (!(new_cut = (t_cut*)malloc(3 * sizeof(t_cut))))
		return (0);
	position = vec3_add_stack(*cone->origin, vec3_mult_stack(c->axis, -0.25));
	new_cut[0].cut_position = vec3_add_stack(*cone->origin, \
	vec3_mult_stack(c->axis, 0.40));
	new_cut[0].cut_normal = vec3_mult_stack(c->axis, -1.0);
	position = vec3_add_stack(*cone->origin, \
	vec3_mult_stack(c->axis, -0.4));
	new_cut[1].cut_position = position;
	new_cut[1].cut_normal = c->axis;
	cone->cut = new_cut;
	cone->nb_cut = 2;
	return (1);
}
