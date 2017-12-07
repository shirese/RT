/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/19 10:53:18 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int				is_cut(t_geo *geo)
{
	return (geo->nb_cut > 0);
}

t_vec3		norm_cut(t_geo *geo, t_hp hp)
{
	t_cut *cut;
	int i;

	i = 0;
	if (is_cut(geo))
	{
		cut = geo->cut;
		while (i < geo->nb_cut)
		{
			if (is_on_cut(&cut[i], hp) == 1)
			{
				//puts("IRIA");
				return (vec3_mult_stack((cut[i].cut_normal), -1));
			}
			i++;
		}
	}
	if (geo->type == 3)
	{
		//puts("MALAZIA");
		return (cylinder_norm(geo, hp));
	}
	else if (geo->type == 2)
		return (cone_normal(geo, hp.p));
	else if (geo->type == 4)
		return (sphere_norm(geo, hp));
    return (vec3_stack(0.0, 0.0, 0.0));
}

int					is_on_cut(t_cut	*cut, t_hp hp)
{
	double res;
	
	res = vec3_dot(vec3_sub_stack(hp.p, cut->cut_position), cut->cut_normal);
	if (fabs(res) <= 0.0000001)
		return (1);
	return (0);
}

int					belong_after_cut(t_geo *geo, t_hp hp)
{
	double res;
	t_cut	*cut;
	int i;

	cut = geo->cut;
	i = 0;
	while (i < geo->nb_cut)
	{
		res = vec3_dot(vec3_sub_stack(hp.p, cut[i].cut_position), cut[i].cut_normal);
		if (res < 0)
			return (0);
		i++;
	}
	return (1);
}



t_hp				first_in_cut(t_geo *geo, t_ray r, t_hp hp_1, t_hp hp_2)
{
    t_hp        hp;
    t_vec3      dir;
	double		to;
	double		ndx;
	double		dn;
	t_cut		*cut;
	int 		i;
	double		born_sup;
	double		born_inf;

	cut = geo->cut;
	born_sup = hp_2.t - hp_1.t;
	born_inf = 0;
	i = 0;
	hp.t = -1;
	if (belong_after_cut(geo, hp_2) == 0)
	{
		//puts("ERTV");
		hp.t = -1;
	}
	else
	{
		while (i < geo->nb_cut)
		{
        	dir = vec3_normalize_stack(r.direction);
        	vec3_normalize(&cut[i].cut_normal);
			ndx = vec3_dot(cut[i].cut_normal, dir);
			dn = vec3_dot(vec3_sub_stack(cut[i].cut_position, hp_1.p), cut[i].cut_normal);	
			to = dn / ndx;
			if (to > 0)
			{  
				if (dn > 0)
					born_sup = min(born_sup, to);
				else
					born_inf = max(to, born_inf); 
			}
			i++;
		}
		if (born_inf <= born_sup)
		{
			hp.t = hp_1.t + min(born_inf, born_sup);
			hp.p = point_at_parameter(hp.t, r);
			hp.normal = norm_cut(geo, hp);
		}
		else
			hp.t = -1;
	}
	return (hp);
}

t_hp				hit_and_cut(t_geo *geo, t_hp hp_1, t_hp hp_2, t_ray r)
{
	if (is_cut(geo) && !belong_after_cut(geo, hp_1))
	{
		return (first_in_cut(geo, r, hp_1, hp_2));
	}
	//puts("renvoie un hp nn null");
	return (hp_1);
}
