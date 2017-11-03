/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic_op_stack.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 12:00:04 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/16 17:58:07 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3				vec3_div_stack(t_vec3 v0, double factor)
{
	t_vec3			v;

	v = vec3_stack(0, 0, 0);
	if (factor != 0)
		v = vec3_stack(v0.x / factor, v0.y / factor, v0.z / factor);
	return (v);
}

t_vec3				vec3_mult_stack(t_vec3 v, double factor)
{
	t_vec3			v_ret;

	v_ret = vec3_stack(v.x * factor, v.y * factor, v.z * factor);
	return (v_ret);
}

t_vec3				vec3_sub_stack(t_vec3 v1, t_vec3 v2)
{
	t_vec3			v;

	v = vec3_stack((v1.x - v2.x), (v1.y - v2.y), (v1.z - v2.z));
	return (v);
}

t_vec3				vec3_add_stack(t_vec3 v1, t_vec3 v2)
{
	t_vec3			v;

	v = vec3_stack((v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z));
	return (v);
}
