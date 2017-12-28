/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negativity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:52:17 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/28 15:15:43 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int				is_scene_dug(t_geo *geo)
{
	t_geo *tmp;

	tmp = geo;
	while (tmp)
	{
		if (tmp->neg)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int			is_geo_dug(t_geo *geo)
{
	if (geo->neg)
		return (1);
	return (0);
}

void		both_solutions(t_ray *r, t_geo *neg, t_hp *sol)
{
	if (neg->type == 2)
		solutions_cone(neg, *r, sol);
	if (neg->type == 3)
		solutions_cylinder(neg, *r, sol);
	if (neg->type == 4)
		solutions_sphere(neg, *r, sol);
}

int					set_borns_neg(t_geo *neg, t_ray r)
{
	t_geo   *tmp;
	t_hp    sol[2];

	tmp = neg;
	while (tmp)
	{
		if (!(tmp->borns_neg = (t_inter*)malloc(sizeof(t_inter))))
			return (0);
		both_solutions(&r, neg, sol);
		tmp->borns_neg->t_start = min(sol[0].t, sol[1].t);
		tmp->borns_neg->t_end = max(sol[0].t, sol[1].t);
		tmp = tmp->next;
	}
	return (1);
}

t_hp                is_touched_by_neg(t_geo *geo, t_ray r, t_hp sol_geo)
{
	t_geo   *neg;

	neg = geo->neg;
	if (set_borns_neg(geo->neg, r) == 0)
	{
		sol_geo.t = -1;
		return (sol_geo);
	}
	while (neg)
	{
		if (sol_geo.t >= neg->borns_neg->t_start && sol_geo.t <= neg->borns_neg->t_end)
		{
			sol_geo.t = -1.0;
			return (sol_geo);
		}
		neg = neg->next;
	}
	return (sol_geo);
}
