/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 13:24:56 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/17 10:45:00 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "rtv1.h"
# include "vector.h"

t_geo				*ray_hit(t_ray *r, t_hp *hp, t_geo *from, t_env *e);
t_ray				shoot_ray(t_vec3 origin, t_vec3 direction, int ray_type);
t_vec3				gen_ray_direction(int i, int j, t_env *e);
t_vec3				gen_ray_origin(t_mat4 cam_to_world, t_vec3 cam_origin);
t_vec3				point_at_parameter(double t, t_ray r);

#endif
