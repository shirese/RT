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

t_vec3				vec3_add_mult_stack(t_vec3 v1, t_vec3 v2, double n)
{
	t_vec3			v;

	v = vec3_stack((v1.x + n * v2.x), (v1.y + n * v2.y), (v1.z + n * v2.z));
	return (v);
}
