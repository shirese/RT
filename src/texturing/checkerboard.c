/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:29:20 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/22 15:21:11 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt.h"
#include "rt_multithread.h"
#include "texture.h"

void				checkerboard_texture(t_vec2 st, t_color *c)
{
	st.x *= 10;
	st.y *= 10;
	if (((int)st.x + (int)st.y) % 2 == 0)
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
