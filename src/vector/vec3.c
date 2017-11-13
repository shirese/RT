/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:57:43 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/12 15:32:59 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "rt.h"
#include "vector.h"

void				vec3_trans(t_vec3 t, t_vec3 *v)
{
	v->x += t.x;
	v->y += t.y;
	v->z += t.z;
}

void				vec3_set(double x, double y, double z, t_vec3 *v)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vec3				vec3_stack(double x, double y, double z)
{
	t_vec3			v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3				*vec3_new(double x, double y, double z)
{
	t_vec3			*v;

	v = malloc(sizeof(t_vec3));
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}
