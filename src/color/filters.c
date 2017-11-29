/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 16:44:31 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/29 11:29:15 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "rt.h"

static void			filter_sepia(int *r, int *g, int *b, t_color *px_col)
{
	*r = 0.393 * *r + 0.769 * *g + 0.189 * *b;
	*r = (*r > 255) ? 255 : *r;
	*g = 0.349 * *r + 0.686 * *g + 0.168 * *b;
	*g = (*g > 255) ? 255 : *g;
	*b = 0.272 * *r + 0.534 * *g + 0.131 * *b;
	*b = (*b > 255) ? 255 : *b;
	color_set(color_new_stack((double)*r / 255, (double)*g / 255, (double)*b / 255, 1.), px_col);
}

void				apply_filters(t_color *px_col, t_env *e)
{
	int				r;
	int				g;
	int				b;

	r = px_col->r * 255;
	g = px_col->g * 255;
	b = px_col->b * 255;
	if (e->filter == 1)
		filter_sepia(&r, &g, &b, px_col);
}
