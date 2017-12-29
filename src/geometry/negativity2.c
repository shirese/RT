/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negativity2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:52:17 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/28 15:37:19 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

double			value_dist_neg(t_geo *geo, t_ray *r, t_hp *sol_geo)
{
	t_geo		*neg;
	double		min;

	min = sol_geo[0].t;
	if (set_borns_neg(geo->neg, r) == 0)
		return (-1);
	
	neg = geo->neg;
	
	while (neg && min != -1)
	{
		if (min > neg->borns_neg->t_start && min < neg->borns_neg->t_end)
		{
			
			if (neg->borns_neg->t_end > sol_geo[1].t)
				min = -1;
			else
			{
				min = neg->borns_neg->t_end;
				neg = geo->neg;
			}
		}
		neg = neg->next;
	}
	
	return (min);
}

static t_vec3	normal_neg(t_geo *geo, t_hp hp)
{
	t_geo		*neg;
	t_vec3		normal;

	neg = geo->neg;
	while (neg)
	{
		if (hp.t == neg->borns_neg->t_start || hp.t == neg->borns_neg->t_end)
		{
			normal = vec3_mult_stack(negative_norm(neg, hp), -1);
			return (normal);
		}
		neg = neg->next;
	}
	normal = negative_norm(geo, hp);
	return (normal);
}

t_hp			first_outside_neg(t_geo *geo, t_ray *r, t_hp *sol_geo)
{
	t_hp		hp_after_neg;
	double		x;

	x = value_dist_neg(geo, r, sol_geo);
	hp_after_neg.t = x;
	if (x != -1)
	{
		hp_after_neg.p = point_at_parameter(x, r);
		hp_after_neg.normal = normal_neg(geo, hp_after_neg);
	}

	return (hp_after_neg);
}

t_hp				first_in_cut_out_neg(t_geo *geo, t_ray *r, t_hp *sol)
{
	t_cut			*cut;
	double			dn;
	int				i;
	double			born_inf;
	double			born_sup;
	int				solution;
	t_hp			sol_new[2];

	t_hp			hp;
	cut = geo->cut;
	born_sup = sol[1].t - sol[0].t;
	born_inf = 0;
	i = 0;
	sol_new[0].t = -1;
	sol_new[1].t = -1;
	solution = 1;
	while (i < geo->nb_cut && solution)
	{
		dn = vec3_dot(vec3_sub_stack(cut[i].cut_position, \
		sol[0].p), cut[i].cut_normal);
		if (set_borns(value_t(cut[i].cut_normal, r, &dn), dn, \
		&born_sup, &born_inf) == 0)
			solution = 0;
		i++;
	}
	if (born_inf <= born_sup && solution)
	{
		sol_new[0].t = sol[0].t + min(born_inf, born_sup);
		sol_new[0].p = point_at_parameter(sol_new[0].t, r);
		sol_new[0].normal = get_norm(geo, sol_new[0]);
		sol_new[1].t = sol[0].t + max(born_inf, born_sup);
		sol_new[1].p = point_at_parameter(sol_new[1].t, r);
		sol_new[1].normal = get_norm(geo, sol_new[1]);	
	}
	return (first_outside_neg(geo, r, sol_new));
}
