/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:16:21 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 16:59:37 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "light.h"
#include "geo.h"
#include "rt.h"
#include "vector.h"

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
