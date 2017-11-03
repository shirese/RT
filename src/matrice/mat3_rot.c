/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 14:17:55 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/19 11:13:48 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "matrice.h"
#include "utils.h"
#include "vector.h"

t_mat3				mat3_x(double t)
{
	t_mat3			mat;

	mat.r1 = vec3_stack(1, 0, 0);
	mat.r2 = vec3_stack(0, cos(t), -sin(t));
	mat.r3 = vec3_stack(0, sin(t), cos(t));
	return (mat);
}

t_mat3				mat3_y(double t)
{
	t_mat3			mat;

	mat.r1 = vec3_stack(cos(t), 0, sin(t));
	mat.r2 = vec3_stack(0, 1, 0);
	mat.r3 = vec3_stack(-sin(t), 0, cos(t));
	return (mat);
}

t_mat3				mat3_z(double t)
{
	t_mat3			mat;

	mat.r1 = vec3_stack(cos(t), -sin(t), 0);
	mat.r2 = vec3_stack(sin(t), cos(t), 0);
	mat.r3 = vec3_stack(0, 0, 1);
	return (mat);
}

t_mat3				mat3_rot_stack(double x, double y, double z)
{
	t_mat3			mat3_rot_stack;

	mat3_rot_stack = mat3_x(deg_to_rad(x));
	mat3_rot_stack = mat3_mult(mat3_rot_stack, mat3_y(deg_to_rad(y)));
	mat3_rot_stack = mat3_mult(mat3_rot_stack, mat3_z(deg_to_rad(z)));
	return (mat3_rot_stack);
}

t_mat3				*mat3_rot(double x, double y, double z)
{
	t_mat3			*mat3_rot;

	mat3_rot = malloc(sizeof(t_mat3));
	if (mat3_rot)
	{
		*mat3_rot = mat3_x(deg_to_rad(x));
		*mat3_rot = mat3_mult(*mat3_rot, mat3_y(deg_to_rad(y)));
		*mat3_rot = mat3_mult(*mat3_rot, mat3_z(deg_to_rad(z)));
	}
	return (mat3_rot);
}
