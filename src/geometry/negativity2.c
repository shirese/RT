/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negativity2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:52:17 by fgallois          #+#    #+#             */
/*   Updated: 2018/01/04 16:19:59 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

double						value_dist_neg(t_geo *geo, t_ray *r, t_hp *sol_geo)
{
	t_geo		*neg;
	double		min;

	min = sol_geo[0].t;
	if (set_borns_neg(geo, r) == 0)
		return (-1);
	neg = geo->neg;
	while (neg && min != -1)
	{
		if (min > neg->borns_neg[0] && \
		min < neg->borns_neg[1])
		{
			if (neg->borns_neg[1] > sol_geo[1].t)
				min = -1;
			else
			{
				min = neg->borns_neg[1];
				neg = geo->neg;
			}
		}
		neg = neg->next;
	}
	return (min);
}

static t_vec3				normal_neg(t_geo *geo, t_hp hp)
{
	t_geo		*neg;
	t_vec3		normal;

	neg = geo->neg;
	while (neg)
	{
		if (hp.t == neg->borns_neg[0] || hp.t == neg->borns_neg[1])
		{
			normal = vec3_mult_stack(negative_norm(neg, hp), -1);
			return (normal);
		}
		neg = neg->next;
	}
	normal = negative_norm(geo, hp);
	return (normal);
}

t_hp						first_outside_neg(t_geo *geo, \
t_ray *r, t_hp *sol_geo)
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

static t_hp					first_in_cut_out_neg2(t_geo *geo, \
t_ray *r, t_hp *sol, t_inter inter)
{
	t_hp	sol_new[2];

	sol_new[0].t = -1;
	sol_new[1].t = -1;
	if (inter.t_start <= inter.t_end)
	{
		sol_new[0].t = sol[0].t + min(inter.t_start, inter.t_end);
		sol_new[0].p = point_at_parameter(sol_new[0].t, r);
		sol_new[0].normal = get_norm(geo, sol_new[0]);
		sol_new[1].t = sol[0].t + max(inter.t_start, inter.t_end);
		sol_new[1].p = point_at_parameter(sol_new[1].t, r);
		sol_new[1].normal = get_norm(geo, sol_new[1]);
	}
	return (first_outside_neg(geo, r, sol_new));
}

t_hp						first_in_cut_out_neg(t_geo *geo, \
t_ray *r, t_hp *sol)
{
	t_cut			*cut;
	t_hp			hp;
	t_inter			inter;
	double			dn;
	int				i;

	cut = geo->cut;
	inter.t_end = sol[1].t - sol[0].t;
	inter.t_start = 0;
	i = 0;
	hp.t = -1;
	while (i < geo->nb_cut)
	{
		dn = vec3_dot(vec3_sub_stack(cut[i].cut_position, \
		sol[0].p), cut[i].cut_normal);
		if (set_borns(value_t(cut[i].cut_normal, r, &dn), dn, \
		&inter.t_end, &inter.t_start) == 0)
			return (hp);
		i++;
	}
	return (first_in_cut_out_neg2(geo, r, sol, inter));
}
