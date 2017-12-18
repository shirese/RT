/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negativity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:52:17 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/14 12:52:18 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int         is_scene_dug(t_geo *geo)
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

int         is_geo_dug(t_geo *geo)
{
    if (geo->neg)
        return (1);
    return (0);
}

void        both_solutions(t_ray *r, t_geo *neg, t_hp *sol)
{
    if (neg->type == 2)
        solutions_cone(neg, *r, sol);
    if (neg->type == 3)
        solutions_cylinder(neg, *r, sol);
    if (neg->type == 4)
        solutions_sphere(neg, *r, sol);
}

int        set_borns_neg(t_geo *geo, t_ray r, t_hp *sol)
{
    t_geo   *neg;

    neg = geo->neg;
    while (neg)
    {
        if (!(neg->borns_neg = (t_inter*)malloc(sizeof(t_inter))))
            return (0);
        both_solutions(&r, neg, sol);
        neg->borns_neg->t_start = min(sol[0].t, sol[1].t);
        neg->borns_neg->t_end = max(sol[0].t, sol[1].t);
        neg = neg->next;
    }
    return (1);
}

double        value_dist_neg(t_geo *geo, t_ray r, t_hp *sol_geo)
{
    t_geo   *neg;
    t_hp    sol[2];
    double min;

    min = sol_geo[0].t;
    if (set_borns_neg(geo, r, sol) == 0)
        return (-1.0);
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

static t_vec3        normal_neg(t_geo *geo, t_hp hp)
{
    t_geo   *neg;
    t_vec3  normal;

    neg = geo->neg;
    while (neg)
    {   
        if (hp.t == neg->borns_neg->t_start || hp.t == neg->borns_neg->t_end)
        {
            normal = vec3_mult_stack(usual_norm(neg, hp), -1);
            return (normal);
        }
         neg = neg->next;
    }
    normal = usual_norm(geo, hp);
    return (normal);
}

t_hp                first_outside_neg(t_geo *geo, t_ray r, t_hp *sol_geo)
{
    t_hp            hp_after_neg;
    double          x;
   
    x = value_dist_neg(geo, r, sol_geo);
    hp_after_neg.t = x;
    if (x != -1)
    {
        hp_after_neg.p = point_at_parameter(x, r);
        hp_after_neg.normal = normal_neg(geo, hp_after_neg);
    }
    return (hp_after_neg);
}
