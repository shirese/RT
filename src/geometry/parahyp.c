/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 15:08:42 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

int					belong_to_parahyp(t_geo *geo, t_vec3 pos)
{
	t_parahyp		*ph;
	double			res;

	ph = (t_parahyp*)geo->curr;
	res = pow((pos.x / ph->facta), 2) - pow((pos.y / ph->factb), 2) - \
		(pos.z / ph->height);
	if (res == 0.0)
		return (1);
	return (0);
}

static t_vec3		parahyp_norm(t_parahyp *ph, t_vec3 hp)
{
	t_vec3			normal;

	normal = vec3_stack(2 * hp.x / pow(ph->facta, 2), -2 * hp.y / \
			pow(ph->factb, 2), -1 / ph->height);
	normal = vec3_normalize_stack(normal);
	return (normal);
}

t_hp				hit_parahyp(t_geo *geo, t_ray r)
{
	t_parahyp		*ph;
	t_hp			hp;
	t_vec3			dir;
	t_vec3			orig;
	double			abcd[4];

	ph = (t_parahyp *)geo->curr;
	dir = r.direction;
	orig = r.origin;
	abcd[0] = pow((dir.x / ph->facta), 2) - pow((dir.y / ph->factb), 2);
	abcd[1] = (2 * orig.x * dir.x / pow(ph->facta, 2)) - (2 * orig.y * dir.y \
			/ pow(ph->factb, 2)) - (dir.z / ph->height);
	abcd[2] = pow((orig.x / ph->facta), 2) - pow((orig.y\
				/ ph->factb), 2) - (orig.z / ph->height);
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] >= 0)
	{
		hp.t = positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
				(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
		hp.p = point_at_parameter(hp.t, r);
		hp.normal = parahyp_norm(ph, hp.p);
	}
	if (hp.t <= 0)
		hp.t = -1;
	return (hp);
}
