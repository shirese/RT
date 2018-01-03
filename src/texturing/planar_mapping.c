/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planar_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:01:02 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/03 11:30:27 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture.h"
#include "vector.h"

int					wrap(double val, int bound)
{
	double			d_coord;
	double			wrap_coord;

	d_coord = val * bound;
	wrap_coord = (int)d_coord % bound;
	if (wrap_coord < 0)
		return ((int)wrap_coord + bound);
	return ((int)wrap_coord);
}

t_vec2				planar_mapping(t_hp *hp, t_geo *geo)
{
	t_vec3			vs;
	t_vec3			vt;
	double			ds;
	double			dt;
	double			integer;

	vs = vec3_stack(1., 0., 0.);
	vt = vec3_stack(0., 1., 0.);
	ds = vec3_dot(hp->p, vs);
	ds = fabs(modf(ds, &integer));
	dt = vec3_dot(hp->p, vt);
	dt = fabs(modf(dt, &integer));
	return (vec2_stack(ds, dt));
}
