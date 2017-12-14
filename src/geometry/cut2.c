/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:50:59 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/14 13:17:23 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

void				print_cut(t_geo *geo)
{
	t_cut			*cut;
	int				i;

	i = 0;
	cut = geo->cut;
	while (i < geo->nb_cut)
	{
		printf("Cut\n\tNormale \n");
		vec3_print(cut[i].cut_normal);
		printf("\tPosition \n");
		vec3_print(cut[i].cut_position);
		printf("\n");
		i++;
	}
}

t_vec3				norm_cut(t_geo *geo, t_hp hp)
{
	t_cut			*cut;
	int				i;

	i = 0;
	if (is_cut(geo))
	{
		cut = geo->cut;
		while (i < geo->nb_cut)
		{
			if (is_on_cut(&cut[i], hp) == 1)
				return (vec3_mult_stack((cut[i].cut_normal), -1));
			i++;
		}
	}
	return (usual_norm(geo, hp));
}

int					set_borns(double to, double dn, double *born_sup, \
double *born_inf)
{
	if (to > 0)
	{
		if (dn < 0)
			*born_sup = min(*born_sup, to);
		else
			*born_inf = max(to, *born_inf);
	}
	else if (dn < 0)
		return (1);
	else
		return (0);
	return (1);
}

double				value_t(t_vec3 normal, t_ray r, double *dn)
{
	double			ndx;
	double			to;

	to = 0;
	vec3_normalize(&normal);
	ndx = vec3_dot(normal, vec3_normalize_stack(r.direction));
	if (ndx != 0.0)
		to = *dn / ndx;
	return (to);
}

double				distance_from_hp1(t_ray r, t_geo *geo, t_hp hp_1, t_hp hp_2)
{
	t_cut			*cut;
	double			dn;
	int				i;
	double			born_inf;
	double			born_sup;

	cut = geo->cut;
	born_sup = hp_2.t - hp_1.t;
	born_inf = 0;
	i = 0;
	while (i < geo->nb_cut)
	{
		dn = vec3_dot(vec3_sub_stack(cut[i].cut_position, \
		hp_1.p), cut[i].cut_normal);
		if (set_borns(value_t(cut[i].cut_normal, r, &dn), dn, \
		&born_sup, &born_inf) == 0)
			return (-1.0);
		i++;
	}
	if (born_inf <= born_sup)
		return (hp_1.t + min(born_inf, born_sup));
	else
		return (-1.0);
}
