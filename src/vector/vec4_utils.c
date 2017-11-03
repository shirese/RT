/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 11:49:51 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/09 15:51:49 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double				vec4_norm(t_vec4 v)
{
	double			v_len;

	v_len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	return (v_len);
}

t_vec4				vec4_normalize_stack(t_vec4 v)
{
	double			v_len;
	t_vec4			v_normalized;

	v_len = vec4_norm(v);
	if (v_len)
	{
		v_normalized.x = v.x / v_len;
		v_normalized.y = v.y / v_len;
		v_normalized.z = v.z / v_len;
		v_normalized.w = v.w / v_len;
		return (v_normalized);
	}
	return (vec4_stack(0., 0., 0., 0.));
}
