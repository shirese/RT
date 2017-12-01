/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toon.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:58:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/01 21:20:22 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "rt.h"
#include "vector.h"

int					get_toon_edges(int geo_type, t_hp hp, t_ray r)
{
	double			v;

	v = vec3_dot(vec3_normalize_stack(\
		vec3_sub_stack(r.origin, hp.p)), hp.normal);
	if (geo_type != 1 && v < 0.3)
		return (1);
	return (0);
}

double				set_toon_lambertian(double *l)
{
	if (*l < 0.1)
		return (0.);
	else if (*l < 0.3)
		return (0.3);
	else if (*l < 0.6)
		return (0.6);
	else
		return (1.);
}
