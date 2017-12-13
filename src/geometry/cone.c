/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 11:45:04 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/13 10:51:24 by fgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

t_hp					c_intersec(t_geo *geo, t_ray r, double *abcd)
{
	t_hp				hp_1;
	t_hp				hp_2;
	double				det;
	t_cone				*c;
	t_vec3				p;

	c = (t_cone *)geo->curr;
	det = sqrt(abcd[3]);
	hp_1.t = positive_smallest((-abcd[1] - det) / (2 * abcd[0]),\
	(-abcd[1] + det) / (2 * abcd[0]));
	hp_1.p = point_at_parameter(hp_1.t, r);
	p = vec3_stack(r.origin.x + hp_1.t * r.direction.x, \
		r.origin.y + hp_1.t * r.direction.y, \
		r.origin.z + hp_1.t * r.direction.z);
	hp_1.normal = norm_cut(geo, hp_1);
	hp_2.t = non_positive_smallest((-abcd[1] - det) / (2 * abcd[0]),\
	(-abcd[1] + det) / (2 * abcd[0]));
	hp_2.p = point_at_parameter(hp_2.t, r);
	p = vec3_stack(r.origin.x + hp_2.t * r.direction.x, \
		r.origin.y + hp_2.t * r.direction.y, \
		r.origin.z + hp_2.t * r.direction.z);
	hp_2.normal = norm_cut(geo, hp_2);
	return (hit_and_cut(geo, hp_1, hp_2, r));
}

double					cone_gamma(double expr, t_geo *geo, t_ray r)
{
	t_cone				*c;
	double				res;

	c = (t_cone *)geo->curr;
	res = pow(beta_cone(expr, c->axis.x, r.origin.x, geo->origin->x), 2) + \
	pow(beta_cone(expr, c->axis.y, r.origin.y, geo->origin->y), 2) + \
	pow(beta_cone(expr, c->axis.z, r.origin.z, geo->origin->z), 2) - \
	pow(beta2_cone(expr, c->axis.x, c->angle), 2) - \
	pow(beta2_cone(expr, c->axis.y, c->angle), 2) - \
	pow(beta2_cone(expr, c->axis.z, c->angle), 2);
	return (res);
}

static double			cone_beta(double *expr, t_geo *geo, t_ray r)
{
	t_cone				*c;
	double				res;

	c = (t_cone *)geo->curr;
	res = (2 * alpha_cone(expr[0], c->axis.x, r.direction.x) *\
		beta_cone(expr[1], c->axis.x, r.origin.x, geo->origin->x)) +\
		(2 * alpha_cone(expr[0], c->axis.y, r.direction.y) *\
		beta_cone(expr[1], c->axis.y, r.origin.y, geo->origin->y)) + \
		(2 * alpha_cone(expr[0], c->axis.z, r.direction.z) *\
		beta_cone(expr[1], c->axis.z, r.origin.z, geo->origin->z)) - \
		(2 * alpha2_cone(expr[0], c->axis.x, c->angle) *\
		beta2_cone(expr[1], c->axis.x, c->angle)) - \
		(2 * alpha2_cone(expr[0], c->axis.y, c->angle) *\
		beta2_cone(expr[1], c->axis.y, c->angle)) - \
		(2 * alpha2_cone(expr[0], c->axis.z, c->angle) *\
		beta2_cone(expr[1], c->axis.z, c->angle));
	return (res);
}

static double			cone_alpha(double expr, t_cone *c, t_ray r)
{
	double				res;

	res = pow(alpha_cone(expr, c->axis.x, r.direction.x), 2) + \
	pow(alpha_cone(expr, c->axis.y, r.direction.y), 2) + \
	pow(alpha_cone(expr, c->axis.z, r.direction.z), 2) - \
	pow(alpha2_cone(expr, c->axis.x, c->angle), 2) - \
	pow(alpha2_cone(expr, c->axis.y, c->angle), 2) - \
	pow(alpha2_cone(expr, c->axis.z, c->angle), 2);
	return (res);
}

t_hp					hit_cone(t_geo *geo, t_ray r)
{
	double				abcd[4];
	double				expr[2];
	t_cone				*c;
	t_hp				hp;

	c = (t_cone *)geo->curr;
	hp.t = -1;
	vec3_normalize(&(c->axis));
	expr[0] = c->axis.x * r.direction.x + c->axis.y * r.direction.y + \
		c->axis.z * r.direction.z;
	expr[1] = (r.origin.x - geo->origin->x) * c->axis.x + (r.origin.y - \
		geo->origin->y) * c->axis.y + (r.origin.z - geo->origin->z) * \
		c->axis.z;
	abcd[0] = cone_alpha(expr[0], c, r);
	abcd[1] = cone_beta(expr, geo, r);
	abcd[2] = cone_gamma(expr[1], geo, r);
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] >= 0)
		return (c_intersec(geo, r, abcd));
	return (hp);
}
