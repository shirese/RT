/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:00:00 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/12 16:29:53 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICE_H
# define MATRICE_H

# include "vector.h"

typedef struct		s_mat4
{
	t_vec4			r1;
	t_vec4			r2;
	t_vec4			r3;
	t_vec4			r4;
}					t_mat4;

typedef struct		s_mat3
{
	t_vec3			r1;
	t_vec3			r2;
	t_vec3			r3;
}					t_mat3;

double				mat3_det(t_mat3 mat);
t_mat3				mat3_inv(t_mat3 mat);
t_mat3				mat3_mult(t_mat3 m1, t_mat3 m2);

t_mat3				mat3_x(double t);
t_mat3				mat3_y(double t);
t_mat3				mat3_z(double t);
t_mat3				mat3_rot_stack(double x, double y, double z);

t_mat3				*mat3_new(t_vec3 r1, t_vec3 r2, t_vec3 r3);
t_mat3				*mat3_rot(double x, double y, double z);

void				mat4_print(t_mat4 m);

t_vec3				mat4_mult_vec3(t_mat4 m, t_vec3 v);
t_mat4				mat4_id(void);
t_mat4				mat4_transf(t_vec4 t, t_vec4 r);
t_mat4				*mat4_new(t_vec4 r1, t_vec4 r2, t_vec4 r3, t_vec4 r4);
t_mat4				*mat4_mult(t_mat4 *m1, t_mat4 m2);

#endif
