/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 11:45:04 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/18 15:39:44 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

static void				c_intersec(t_geo *geo, t_ray r, double *abcd, t_hp *hp)
{
	double				det;
	double				t0;
	double				t1;
	t_cone				*c;
	t_vec3				p;

	det = sqrt(abcd[3]);
	t0 = (-abcd[1] - det) / (2 * abcd[0]);
	t1 = (-abcd[1] + det) / (2 * abcd[0]);
	c = (t_cone *)geo->curr;
	hp->t = positive_smallest(t0, t1);
	hp->p = point_at_parameter(hp->t, r);
	p = vec3_stack(r.origin.x + hp->t * r.direction.x, \
		r.origin.y + hp->t * r.direction.y, \
		r.origin.z + hp->t * r.direction.z);
	hp->normal = cone_normal(geo, c, p);
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
	{
		c_intersec(geo, r, abcd, &hp);
		return (hp);
	}
	return (hp);
}
