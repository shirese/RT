/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planar_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:01:02 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/14 14:23:16 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture.h"
#include "vector.h"

t_vec2				planar_mapping(t_hp hp, t_geo *geo)
{
	t_vec3			vs;
	t_vec3			vt;
	double			ds;
	double			dt;


	vs = vec3_stack(1., 0., 0.);
	vt = vec3_stack(0., 1., 0.);
	ds = dt = geo->origin->z;
	return (vec2_stack(ds + vec3_dot(hp.p, vs), dt + vec3_dot(hp.p, vt)));
}
