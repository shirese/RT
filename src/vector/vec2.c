/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:32:15 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/12 15:32:58 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "vector.h"

t_vec2				vec2_stack(double x, double y)
{
	t_vec2			v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec2				*vec2_new(double x, double y)
{
	t_vec2			*v;

	v = malloc(sizeof(t_vec2));
	v->x = x;
	v->y = y;
	return (v);
}

