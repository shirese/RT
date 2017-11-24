/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 13:24:56 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/06 12:38:57 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "rt.h"
# include "vector.h"

t_geo				*ray_hit(t_ray *r, t_hp *hp, t_geo *from, t_env *e);
t_ray				init_ray(t_vec3 origin, t_vec3 direction, int ray_type);
t_vec3				gen_ray_direction(double i, double j, t_env *e);
t_vec3				gen_ray_origin(t_mat4 cam_to_world, t_vec3 cam_origin);
t_vec3				point_at_parameter(double t, t_ray r);
void				translate_ray(t_ray *r, t_hp hp);
#endif
