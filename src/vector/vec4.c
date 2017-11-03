/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 12:06:42 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/04 12:10:52 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec4				vec4_stack(double x, double y, double w, double z)
{
	t_vec4			v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
}

t_vec4				*vec4_new(double x, double y, double z, double w)
{
	t_vec4			*v;

	v = malloc(sizeof(t_vec4));
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = w;
	return (v);
}
