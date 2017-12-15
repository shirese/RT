/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 14:34:15 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/15 11:27:09 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "light.h"
#include "matrice.h"
#include "rt.h"

t_ray				init_ray(t_vec3 origin, t_vec3 dir, int r_type, float ior)
{
	t_ray			r;

	r.origin = origin;
	r.direction = vec3_normalize_stack(dir);
	r.color = color_new_stack(0.0, 0.0, 0.0);
	r.type = r_type;
	r.ior = ior;
	r.rec = 0;
	if (r.type == 1)
	{
		r.origin.x += 0.000001;
		r.origin.y += 0.000001;
		r.origin.z += 0.000001;
	}
	return (r);
}

t_vec3				point_at_parameter(double t, t_ray r)
{
	t_vec3			pap;
	t_vec3			tmp;

	tmp = vec3_mult_stack(r.direction, t);
	pap = vec3_add_stack(r.origin, tmp);
	return (pap);
}

t_vec3				gen_ray_direction(double i, double j, t_env *e)
{
	double			x;
	double			y;
	t_vec3			ray_direction;

	x = (2 * (i + 0.5) / e->scr.nx - 1) * e->scr.scale;
	y = (1 - 2 * (j + 0.5) / e->scr.ny) * e->scr.scale * 1 / e->scr.asp_ratio;
	ray_direction = mat4_mult_vec3(*e->cam->cam_to_world, \
		vec3_stack(x, y, -1.));
	vec3_normalize(&ray_direction);
	return (ray_direction);
}

t_vec3				gen_ray_origin(t_mat4 cam_to_world, t_vec3 cam_origin)
{
	t_vec3			ray_origin;

	ray_origin = mat4_mult_vec3(cam_to_world, cam_origin);
	return (ray_origin);
}
