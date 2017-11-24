/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 16:08:25 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/07 11:38:46 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "rt.h"

void				color_print(t_color c)
{
	ft_printf("[R %f G %f B %f A %f]\n", c.r, c.g, c.b, c.a);
}



void			color_add_mult(t_color c1, t_color *c2, double fact)
{
	if (c2)
	{
		c2->r += fact * c1.r;
		c2->g += fact * c1.g;
		c2->b += fact * c1.b;
		color_clamp(c2, 0.0, 1.0);
	}
}
