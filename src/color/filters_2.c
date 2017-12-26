/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 11:57:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/26 12:12:22 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt.h"

void				filter_saturate(t_color *px_col)
{
	color_mult_fac(px_col, 1.5);
}

void				filter_sunset(t_color *px_col)
{
	double			brightness;

	brightness = (px_col->r + px_col->g + px_col->b) / 3.;
	if (brightness < 0.2)
		color_mult(color_new_stack(46 / 255., 17 / 255., 45 / 255.), px_col);
	else if (brightness < 0.4)
		color_mult(color_new_stack(84 / 255., 0 / 255., 50 / 255.), px_col);
	else if (brightness < 0.6)
		color_mult(color_new_stack(130 / 255., 3 / 255., 51 / 255.), px_col);
	else if (brightness < 0.8)
		color_mult(color_new_stack(201 / 255., 40 / 255., 62 / 255.), px_col);
	else
		color_mult(color_new_stack(240 / 255., 67 / 255., 58 / 255.), px_col);
}
