/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:29:20 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/12 16:54:21 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt.h"
#include "texture.h"

t_color				checkerboard_texture(t_vec2 st)
{
	st.x *= 10;
	st.y *= 10;
	if (((int)st.x + (int)st.y) % 2 == 0)
		return (color_new_stack(1., 1., 1., 1.));
	return (color_new_stack(0., 0., 0., 1.));
}
