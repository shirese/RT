/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:56:56 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/12 13:55:38 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void				vec3_mult_fact(t_vec3 *v, double factor)
{
	v->x *= factor;
	v->y *= factor;
	v->z *= factor;
}

t_vec3				*vec3_div(t_vec3 v0, double factor)
{
	t_vec3			*v;

	v = NULL;
	if (factor != 0)
		v = vec3_new(v0.x / factor, v0.y / factor, v0.z / factor);
	return (v);
}

t_vec3				*vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3			*v;

	v = vec3_new((v1.x - v2.x), (v1.y - v2.y), (v1.z - v2.z));
	return (v);
}

t_vec3				*vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3			*v;

	v = vec3_new((v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z));
	return (v);
}

t_vec3				*vec3_mult(t_vec3 *v, double factor)
{
	t_vec3			*v_ret;

	v_ret = vec3_new(v->x * factor, v->y * factor, v->z * factor);
	return (v_ret);
}
