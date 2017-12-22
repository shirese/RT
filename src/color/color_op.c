/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:33:21 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/22 11:47:11 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

void				color_div(t_color c1, t_color *c2)
{
	if (c2)
	{
		c2->r /= c1.r;
		c2->g /= c1.g;
		c2->b /= c1.b;
		color_clamp(c2, 0.0, 1.0);
	}
}

void				color_mult(t_color c1, t_color *c2)
{
	if (c2)
	{
		c2->r *= c1.r;
		c2->g *= c1.g;
		c2->b *= c1.b;
		color_clamp(c2, 0.0, 1.0);
	}
}

void				color_add_no_clamp(t_color c1, t_color *c2)
{
	if (c2)
	{
		c2->r += c1.r;
		c2->g += c1.g;
		c2->b += c1.b;
	}
}

void				color_add(t_color c1, t_color *c2)
{
	if (c2)
	{
		c2->r += c1.r;
		c2->g += c1.g;
		c2->b += c1.b;
		color_clamp(c2, 0.0, 1.0);
	}
}

void				color_clamp(t_color *c, double min, double max)
{
	c->r = clamp(c->r, min, max);
	c->g = clamp(c->g, min, max);
	c->b = clamp(c->b, min, max);
}
