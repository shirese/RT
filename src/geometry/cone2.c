/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 10:19:11 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/22 16:21:28 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rt.h"
#include "vector.h"

t_vec3				cone_norm(t_geo *geo, t_vec3 p)
{
	t_cone			*c;
	t_vec3			h;
	t_vec3			v;
	t_vec3			sub;
	t_vec3			add;

	c = (t_cone*)geo->curr;
	sub = vec3_sub_stack(p, *geo->origin);
	h = vec3_mult_stack(c->axis, vec3_dot(sub, c->axis));
	add = vec3_add_stack(*geo->origin, h);
	v = vec3_sub_stack(p, add);
	vec3_normalize(&v);
	return (v);
}

double				beta2_cone(double expr, double n, double angle)
{
	return (expr * n * tan(angle));
}

double				beta_cone(double expr, double n, double a, double o)
{
	return (n * expr + o - a);
}

double				alpha2_cone(double expr, double n, double angle)
{
	return (expr * n * tan(angle));
}

double				alpha_cone(double expr, double n, double dir)
{
	return (n * expr - dir);
}
