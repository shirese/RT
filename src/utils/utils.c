/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:16:21 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/04 12:54:14 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "light.h"
#include "geo.h"
#include "rt.h"
#include "utils.h"
#include "vector.h"

void				print_env(t_env *e)
{
	t_geo			*geo;

	ft_printf("\n\n///////////		ENV		///////////\n\n");
	ft_printf("WIN\t\t%d*%d\n", e->win.w, e->win.h);
	ft_printf("SCREEN\t\tRATIO [%f] SCALE [%f]\n", e->scr.asp_ratio, \
		e->scr.scale);
	ft_printf("CAM\t\t");
	vec3_print(*e->cam->pos);
	ft_printf("\nFOV\t\t[%f]\n", e->cam->fov);
	print_lights(e);
	geo = e->geos;
	while (geo)
	{
		print_geo(geo);
		print_cut(geo);
		geo = geo->next;
	}
}

static void			atof_cson_norme(int d, double *f, double *r, char **str)
{
	if (d)
		*f /= 10.0f;
	*r = *r * 10.0f + (double)(**str - '0');
}

double				atof_cson(char **str)
{
	double			rez;
	double			fact;
	int				dot_seen;

	rez = 0;
	fact = 1;
	dot_seen = 0;
	while (**str == ' ')
		(*str)++;
	if (**str == '-' && ((*str)++))
		fact = -1;
	else if (**str == '+' && ((*str)++))
		fact = 1;
	while ((ft_isdigit(**str) || **str == '.') && **str != '\0')
	{
		if (dot_seen == 0 && **str == '.')
			dot_seen = 1;
		else if (ft_isdigit(**str))
			atof_cson_norme(dot_seen, &fact, &rez, str);
		(*str)++;
	}
	(*str) += 2;
	return (rez * fact);
}
