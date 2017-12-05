/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:42:59 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/05 15:37:03 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ray.h"
#include "rt.h"

t_color				get_px_col(int x, int y, t_env *e)
{
	double			ij[2];
	double			px_pos[2];
	static double	samp_count;
	t_color			px_col;

	if (e->samp_rate == 1)
		return (find_ray_color(x, y, e));
	px_col = color_new_stack(0., 0., 0.);
	ij[0] = 0;
	if (!samp_count)
		samp_count = 1 / (pow((e->samp_rate / 2), 2));
	while (ij[0]++ < e->samp_rate / 2)
	{
		ij[1] = 0;
		while (ij[1]++ < e->samp_rate / 2)
		{
			px_pos[0] = x + ij[0] / (e->samp_rate / 2);
			px_pos[1] = y + ij[1] / (e->samp_rate / 2);
			color_add_no_clamp(find_ray_color(px_pos[0], px_pos[1], e), &px_col);
		}
	}
	px_col.r *= samp_count;
	px_col.g *= samp_count;
	px_col.b *= samp_count;
	return (px_col);
}
