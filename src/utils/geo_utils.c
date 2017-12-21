/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 12:06:59 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/05 12:08:14 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "rt.h"

int					belong_to(t_geo *g, t_vec3 pos)
{
	if (g->type == 1)
		return (belong_to_plane(g, pos));
	else if (g->type == 2)
		return (belong_to_cone(g, pos));
	else if (g->type == 3)
		return (belong_to_cylinder(g, pos));
	else if (g->type == 4)
		return (belong_to_sphere(g, pos));
	else if (g->type == 5)
		return (belong_to_disk(g, pos));
	return (0);
}
