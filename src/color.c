/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 12:25:51 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/13 16:14:23 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rtv1.h"

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

void				color_mult(t_color c1, t_color *c2)
{
	if (c2)
	{
		c2->r *= c1.r;
		c2->g *= c1.g;
		c2->b *= c1.b;
		clamp_color(c2, 0.0, 1.0);
	}
}

void				color_add(t_color c1, t_color *c2)
{
	if (c2)
	{
		c2->r += c1.r;
		c2->g += c1.g;
		c2->b += c1.b;
		clamp_color(c2, 0.0, 1.0);
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
