/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:42:59 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/10 17:27:46 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "ray.h"
#include "rt.h"

t_color				get_px_col(int x, int y, t_env *e)
{
	double			ij[2];
	double			px_pos[2];
	static double	samp_count;
	t_color			px_c;

	if (e->samp_rate == 1)
		return (find_ray_color(x, y, e));
	px_c = color_new_stack(0., 0., 0.);
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
			color_add_no_clamp(find_ray_color(px_pos[0], px_pos[1], e), &px_c);
		}
	}
	px_c.r *= samp_count;
	px_c.g *= samp_count;
	px_c.b *= samp_count;
	return (px_c);
}
