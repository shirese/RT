/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 10:19:11 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/18 17:41:05 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rt.h"
#include "vector.h"

int					belong_to_cone(t_geo *geo, t_vec3 pos)
{
	t_cone		    *c;
	t_vec3			diff;
	t_vec3			proj;
	t_vec3			dif;
    t_vec3          oh;

	c = (t_cone*)geo->curr;
	diff = vec3_sub_stack(*geo->origin, pos);
	proj = vec3_add_mult_stack(*geo->origin, c->axis, vec3_dot(diff, c->axis));
	dif = vec3_sub_stack(proj, pos);
    oh =  vec3_sub_stack(proj, *geo->origin); 
	if (vec3_norm(dif) <= tan(c->angle) * vec3_norm(oh))
		return (1);
	return (0);
}
