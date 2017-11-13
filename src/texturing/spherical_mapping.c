/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_mapping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 14:13:10 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/13 12:43:56 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrice.h"
#include "rt.h"
#include "utils.h"
#include "vector.h"

static float			spherical_theta(t_vec3 v)
{
	return (acos(clamp(v.z, -1., 1.)));
}

static float			spherical_phi(t_vec3 v)
{
	float				p;

	p = atan2(v.y, v.x);
	return (p < 0) ? (p + 2 * M_PI) : p;
}

t_vec2					sphere_map(t_vec3 p, t_geo *geo)
{
	double				theta;
	double				phi;
	t_mat4				world_to_tex;
	t_vec3				v;

	v = vec3_normalize_stack(vec3_sub_stack(p, *geo->origin));
	theta = spherical_theta(v);
	phi = spherical_phi(v);
	return (vec2_stack(theta * INV_PI, phi * INV2_PI));
}


t_vec2					sphere_mapping(t_hp hp, t_geo *geo)
{
	t_vec2				st;

	st = sphere_map(hp.p, geo);
	return (st);
}
