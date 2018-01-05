/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:29:20 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/03 14:02:57 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt.h"
#include "rt_multithread.h"
#include "texture.h"

static double		modulo(double x)
{
	return (x - floor(x));
}

void				checkerboard_texture(t_vec2 st, t_vec3 pos, t_color *c)
{
	int				pattern;

	if (pos.x < 0)
		st.x -= 0.5;
	if (pos.y < 0)
		st.y -= 0.5;
	pattern = (modulo(st.y * CHECKER_SIZE) < 0.5) ^ \
		(modulo(st.x * CHECKER_SIZE) < 0.5);
	if (pattern == 0)
	{
		c->r = 1.;
		c->g = 1.;
		c->b = 1.;
	}
	else
	{
		c->r = 0.;
		c->g = 0.;
		c->b = 0.;
	}
}
