/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 16:19:56 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/18 17:37:26 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int					belong_to_sphere(t_geo *geo, t_vec3 pos)
{
	t_sphere	*sphere;
	t_vec3		diff;
	
	sphere = (t_sphere*)geo->curr;
	diff = vec3_sub_stack(*geo->origin, pos);
	if (vec3_norm(diff) <= sphere->radius)
		return (1);
	return (0);
}

t_hp				hit_sphere(t_geo *geo, t_ray r)
{
	double			abcd[4];
	double			t[2];
	t_hp			hp;
	t_vec3			oc;
	t_sphere		*sphere;

	hp.t = -1;
	sphere = (t_sphere *)geo->curr;
	oc = vec3_sub_stack(r.origin, *geo->origin);
	abcd[0] = vec3_dot(r.direction, r.direction);
	abcd[1] = 2.0 * vec3_dot(oc, r.direction);
	abcd[2] = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] > 0)
	{
		t[0] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
		t[1] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
		hp.t = positive_smallest(t[0], t[1]);
		hp.p = point_at_parameter(hp.t, r);
		hp.normal = vec3_sub_stack(hp.p, *geo->origin);
		vec3_normalize(&hp.normal);
	}
	return (hp);
}
