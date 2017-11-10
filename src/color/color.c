/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 12:25:51 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/07 11:37:34 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt.h"

void				color_set(t_color c, t_color *c_to_set)
{
	if (c_to_set)
	{
		c_to_set->r = c.r;
		c_to_set->g = c.g;
		c_to_set->b = c.b;
		c_to_set->a = c.a;
	}
}

t_color				color_new_stack(double r, double g, double b, double a)
{
	t_color			c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}

t_color				*color_new(double r, double g, double b, double a)
{
	t_color			*c;

	c = malloc(sizeof(t_color));
	if (!c)
		return (NULL);
	c->r = r;
	c->g = g;
	c->b = b;
	c->a = a;
	return (c);
}
