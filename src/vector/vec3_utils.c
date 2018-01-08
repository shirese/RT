/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 12:03:03 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/08 10:45:21 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "vector.h"

void				vec3_rev(t_vec3 *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}

double				vec3_norm(t_vec3 v)
{
	double			v_len;

	v_len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (v_len);
}

t_vec3				vec3_normalize_stack(t_vec3 v)
{
	double			v_len;
	t_vec3			v_normalized;

	v_len = vec3_norm(v);
	if (v_len)
	{
		v_normalized.x = v.x / v_len;
		v_normalized.y = v.y / v_len;
		v_normalized.z = v.z / v_len;
		return (v_normalized);
	}
	return (vec3_stack(0., 0., 0.));
}

void				vec3_normalize(t_vec3 *v)
{
	double			v_len;

	v_len = vec3_norm(*v);
	if (v_len)
	{
		v->x /= v_len;
		v->y /= v_len;
		v->z /= v_len;
	}
}

void				vec3_print(t_vec3 v)
{
	ft_printf("[%f %f %f]\n", v.x, v.y, v.z);
}
