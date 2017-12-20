/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/14 14:00:54 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

void				fill_solution_cylinder(t_geo *geo, t_ray r, \
double *abcd, t_hp *sol)
{
	sol[0].t = positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
			(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
	sol[0].p = point_at_parameter(sol[0].t, r);
	sol[0].normal = cylinder_norm(geo, sol[0]);
	sol[1].t = non_positive_smallest((-abcd[1] - sqrt(abcd[3])) / \
	(2 * abcd[0]), (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
	sol[1].p = point_at_parameter(sol[1].t, r);
	sol[1].normal = cylinder_norm(geo, sol[1]);
}
