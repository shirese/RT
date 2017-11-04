/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 16:08:25 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/13 16:08:41 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt.h"

void				clamp_color(t_color *c, double min, double max)
{
	c->r = clamp(c->r, min, max);
	c->g = clamp(c->g, min, max);
	c->b = clamp(c->b, min, max);
}
