/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:39:23 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/12 15:49:33 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "texture.h"
#include "rt.h"

t_color					compute_uv_texture(t_vec2 st)
{
	t_color				c;

	c = color_new_stack(0., 0., 0., 1.);
	c.r = st.x - floor(st.x);
	c.g = st.y - floor(st.y);
	c.b = 0.;
	return (c);
}
