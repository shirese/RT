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

int					belong_to_pipe(t_geo *geo, t_vec3 pos)
{
	t_pipe		    *pip;
	t_vec3			diff;
	t_vec3			dif;
	t_vec3			proj;
	double 			len;

	pip = (t_pipe*)geo->curr;
    diff = vec3_sub_stack(pos, *geo->origin);
	len = vec3_dot(diff, pip->axis);
	if (fabs(len) > pip->height / 2)
        return (0);
	proj = vec3_add_mult_stack(*geo->origin, pip->axis, len);
	dif = vec3_sub_stack(proj, pos);
    /*if (vec3_norm(dif) > pip->radius)
        return (0);*/
    return (1);
}

int					belong_to_pipe_2(t_geo *geo, t_vec3 pos)
{
	t_pipe		    *pip;
	t_vec3			diff;
	t_vec3			dif;
	t_vec3			proj;
	double 			len;

	pip = (t_pipe*)geo->curr;
    diff = vec3_sub_stack(pos, *geo->origin);
	len = vec3_dot(diff, pip->axis);
	if (fabs(len) > pip->height / 2)
        return (0);
	proj = vec3_add_mult_stack(*geo->origin, pip->axis, len);
	dif = vec3_sub_stack(proj, pos);
//	printf("Norm %f %f \n", vec3_norm(dif), pip->radius);
    if (vec3_norm(dif) > pip->radius)
        return (0);
    return (1);
}

static t_vec3		pipe_norm(t_geo *geo, t_pipe *pipe, t_vec3 hp)
{
	t_vec3			normal;
	t_vec3			tmp;
	t_vec3			project;
	float			dot;

	tmp = vec3_sub_stack(hp, *geo->origin);
	dot = vec3_dot(tmp, pipe->axis);
	
	if (fabs(dot) == pipe->height / 2)
	{
		if (dot > 0)
			return (pipe->axis);
		else
			return (vec3_mult_stack(pipe->axis, -1));
	}
	project = vec3_mult_stack(pipe->axis, dot);
	normal = vec3_sub_stack(tmp, project);
	vec3_normalize(&normal);
	return (normal);
}


t_hp				first_inside_pipe(t_geo *geo, t_ray r, t_hp hp_1, t_hp hp_2)
{
	t_pipe	*pip;
	t_hp	hp_3;
	t_vec3 dir;
	t_vec3 od;
	t_vec3 normal;
	double a;
	double delta;

	pip = (t_pipe *)geo->curr;
	dir = vec3_sub_stack(hp_2.p, hp_1.p);
	dir = vec3_normalize_stack(dir);
	od = vec3_sub_stack(hp_1.p, *geo->origin);
	/*printf("HP 1 %f %f %f %f \n", hp_1.t,  hp_1.p.x, hp_1.p.y, hp_1.p.z);
	printf("HP 2 %f %f %f %f\n", hp_2.t, hp_2.p.x, hp_2.p.y, hp_2.p.z);
	printf("dir %f %f %f \n", dir.x, dir.y, dir.z);*/
	a = vec3_dot(od, pip->axis);
	normal = pip->axis;
	if (a < 0)
	{
		a = -a;
		normal = vec3_mult_stack(normal, -1.0);
	}
	delta = vec3_dot(dir, normal);
	
	
	hp_3.t = hp_1.t + positive_smallest((pip->height/ 2 - a)/ delta, - (pip->height/2 + a )/ delta);
	//hp_3.t = hp_1.t + positive_smallest((pip->height - a)/ delta, - (pip->height + a )/ delta);
	//hp_3.t = hp_1.t + positive_smallest( (-a / delta) + (pip->height / 2 * fabs(delta)), (-a / delta) - (pip->height / 2 * fabs(delta)));
	//printf("PSM %f %f %f %f \n ", pip->height, a ,delta, hp_3.t);
	hp_3.p = point_at_parameter(hp_3.t, r);
	hp_3.normal = pipe_norm(geo, pip, hp_3.p);
	//if (vec3_dot(hp_3.p, pip->axis) < 0)
	//	printf("HP_3 %f\n", hp_3.t - hp_1.t);
	return (hp_3);
}	

t_hp				hit_pipe(t_geo *geo, t_ray r)
{
	t_pipe		    *pip;
	t_hp			hp_1;
	t_hp			hp_2;
	t_vec3			x;
	double			abcd[4];
	double			dot[2];

	hp_1.t = -1;
	pip = (t_pipe *)geo->curr;
	x = vec3_sub_stack(r.origin, *geo->origin);
	vec3_normalize(&pip->axis);
	dot[0] = vec3_dot(r.direction, pip->axis);
	dot[1] = vec3_dot(x, pip->axis);
	abcd[0] = vec3_dot(r.direction, r.direction) - dot[0] * dot[0];
	abcd[1] = 2 * (vec3_dot(r.direction, x) - dot[0] * dot[1]);
	abcd[2] = vec3_dot(x, x) - dot[1] * dot[1] - pip->radius * pip->radius;
	abcd[3] = abcd[1] * abcd[1] - 4 * abcd[0] * abcd[2];
	if (abcd[3] > 0)
	{
		hp_1.t = positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
			(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
		hp_1.p = point_at_parameter(hp_1.t, r);
		hp_1.normal = pipe_norm(geo, pip, hp_1.p);
		if (hp_1.t != -1 && belong_to_pipe(geo, hp_1.p) == 1)
			hp_1.normal = pipe_norm(geo, pip, hp_1.p);	
		else if (hp_1.t != -1)
		{
			hp_2.t = non_positive_smallest((-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]), \
			(-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]));
			hp_2.p = point_at_parameter(hp_2.t, r);
			if (hp_2.t != -1.0 && belong_to_pipe(geo, hp_2.p) == 1)
				return (first_inside_pipe(geo, r, hp_1, hp_2));
			else
				hp_1.t = -1;
		}
	}
	else if (abcd[3] == 0)
	{
		hp_1.t = -abcd[1] / (2 * abcd[0]);
		hp_1.p = point_at_parameter(hp_1.t, r);
		hp_1.normal = pipe_norm(geo, pip, hp_1.p);
		if (hp_1.t != -1 && belong_to_pipe(geo, hp_1.p) == 0)
			hp_1.t = -1;
	}
    return (hp_1);
}
