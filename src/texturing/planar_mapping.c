/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planar_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:01:02 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/04 12:21:49 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture.h"
#include "vector.h"

t_vec2				planar_mapping(t_hp *hp)
{
	t_vec3			vs;
	t_vec3			vt;
	double			ds;
	double			dt;
	double			integer;

	if (fabs(hp->normal.x) == 1)
		vs = vec3_stack(0., 0., 1.);
	else
		vs = vec3_stack(1., 0., 0.);
	vt = vec3_cross_prod_stack(hp->normal, vs);
	ds = vec3_dot(hp->p, vs);
	ds = fabs(modf(ds, &integer));
	dt = vec3_dot(hp->p, vt);
	dt = fabs(modf(dt, &integer));
	return (vec2_stack(ds, dt));
}
