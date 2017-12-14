/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 16:19:56 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/14 12:27:40 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int					belong_to_sphere(t_geo *geo, t_vec3 pos)
{
	t_sphere		*sphere;
	t_vec3			diff;

	sphere = (t_sphere*)geo->curr;
	diff = vec3_sub_stack(*geo->origin, pos);
	if (vec3_norm(diff) <= sphere->radius)
		return (1);
	return (0);
}

t_vec3		sphere_norm(t_geo *geo, t_hp hp)
{
	return (vec3_normalize_stack(vec3_sub_stack(hp.p, *geo->origin)));
}

t_hp				hit_sphere(t_geo *geo, t_ray r)
{
	double			abcd[4];
	double			t[2];
	t_hp			hp_1;
	t_hp			hp_2;
	t_vec3			oc;
	t_sphere		*sphere;


	hp_1.t = -1;
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
		hp_1.t = positive_smallest(t[0], t[1]);
		hp_1.p = point_at_parameter(hp_1.t, r);
		hp_1.normal = norm_cut(geo, hp_1);
		hp_2.t = non_positive_smallest(t[0], t[1]);
		hp_2.p = point_at_parameter(hp_2.t, r);
		hp_2.normal = norm_cut(geo, hp_2);
		return (hit_and_cut(geo, hp_1, hp_2, r));
	}
	return (hp_1);
}
