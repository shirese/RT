/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:42:47 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/08 08:26:20 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

void				color_div_fac(t_color *c, int fac)
{
	if (c)
	{
		c->r /= fac;
		c->g /= fac;
		c->b /= fac;
	}
}

void				color_mult_fac(t_color *c, double fac)
{
	if (c)
	{
		c->r *= fac;
		c->g *= fac;
		c->b *= fac;
	}
}

