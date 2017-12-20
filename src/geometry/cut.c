/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:50:30 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/14 13:15:10 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int					is_cut(t_geo *geo)
{
	return (geo->nb_cut > 0);
}

int					is_on_cut(t_cut *cut, t_hp hp)
{
	double			res;

	res = vec3_dot(vec3_sub_stack(hp.p, cut->cut_position), cut->cut_normal);
	if (fabs(res) <= 0.0000001)
		return (1);
	return (0);
}

int					belong_after_cut(t_geo *geo, t_vec3 pos)
{
	double			res;
	t_cut			*cut;
	int				i;

	cut = geo->cut;
	i = 0;
	while (i < geo->nb_cut)
	{
		res = vec3_dot(vec3_sub_stack(pos, cut[i].cut_position), \
		cut[i].cut_normal);
		if (res < 0)
			return (0);
		i++;
	}
	return (1);
}

t_hp				first_in_cut(t_geo *geo, t_ray r, t_hp hp_1, t_hp hp_2)
{
	t_hp			hp;
	double			dist;

	hp.t = -1;
	dist = distance_from_hp1(r, geo, hp_1, hp_2);
	if (dist != -1.0)
	{
		hp.t = dist;
		hp.p = point_at_parameter(hp.t, r);
		hp.normal = cut_norm(geo, hp);
	}
	return (hp);
}

t_hp				hit_and_cut(t_geo *geo, t_hp hp_1, t_hp hp_2, t_ray r)
{
	if (is_cut(geo) && !belong_after_cut(geo, hp_1.p))
		return (first_in_cut(geo, r, hp_1, hp_2));
	return (hp_1);
}
