/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_adv_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 12:02:32 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/12 13:55:29 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double				vec3_dot(t_vec3 v1, t_vec3 v2)
{
	double			res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

t_vec3				vec3_cross_prod_stack(t_vec3 v1, t_vec3 v2)
{
	t_vec3			v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vec3				*vec3_cross_prod(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3		*v;

	v = malloc(sizeof(t_vec3));
	v->x = v1->y * v2->z - v1->z * v2->y;
	v->y = v1->z * v2->x - v1->x * v2->z;
	v->z = v1->x * v2->y - v1->y * v2->x;
	return (v);
}
