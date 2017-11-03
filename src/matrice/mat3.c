/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:57:16 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/04 16:10:14 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrice.h"
#include "vector.h"

double				mat3_det(t_mat3 mat)
{
	double			res;

	res = 0;
	res += mat.r1.x * mat.r2.y * mat.r3.z;
	res += mat.r2.x * mat.r3.y * mat.r1.z;
	res += mat.r3.x * mat.r1.y * mat.r2.z;
	res -= mat.r1.x * mat.r3.y * mat.r2.z;
	res -= mat.r3.x * mat.r2.y * mat.r1.z;
	res -= mat.r2.x * mat.r1.y * mat.r3.z;
	return (res);
}

t_mat3				mat3_inv(t_mat3 mat)
{
	t_mat3			res;
	double			det;

	det = mat3_det(mat);
	res.r1 = vec3_stack((mat.r2.y * mat.r3.z)
			- (mat.r2.z * mat.r3.y), (mat.r1.z * mat.r3.y)
			- (mat.r1.y * mat.r3.z), (mat.r1.y * mat.r2.z)
			- (mat.r1.z * mat.r2.y));
	res.r2 = vec3_stack((mat.r2.z * mat.r3.x)
			- (mat.r2.x * mat.r3.z), (mat.r1.x * mat.r3.z)
			- (mat.r1.z * mat.r3.x), (mat.r1.z * mat.r2.x)
			- (mat.r1.x * mat.r2.z));
	res.r3 = vec3_stack((mat.r2.x * mat.r3.y)
			- (mat.r2.y * mat.r3.x), (mat.r1.y * mat.r3.x)
			- (mat.r1.x * mat.r3.y), (mat.r1.x * mat.r2.y)
			- (mat.r1.y * mat.r2.x));
	res.r1 = vec3_mult_stack(res.r1, 1.0 / det);
	res.r2 = vec3_mult_stack(res.r2, 1.0 / det);
	res.r3 = vec3_mult_stack(res.r3, 1.0 / det);
	return (res);
}

t_mat3				mat3_mult(t_mat3 m1, t_mat3 m2)
{
	t_mat3			res;
	double			a;
	double			b;
	double			c;

	a = (m1.r1.x * m2.r1.x) + (m1.r1.y * m2.r2.x) + (m1.r1.z * m2.r3.x);
	b = (m1.r1.x * m2.r1.y) + (m1.r1.y * m2.r2.y) + (m1.r1.z * m2.r3.y);
	c = (m1.r1.x * m2.r1.z) + (m1.r1.y * m2.r2.z) + (m1.r1.z * m2.r3.z);
	res.r1 = vec3_stack(a, b, c);
	a = (m1.r2.x * m2.r1.x) + (m1.r2.y * m2.r2.x) + (m1.r2.z * m2.r3.x);
	b = (m1.r2.x * m2.r1.y) + (m1.r2.y * m2.r2.y) + (m1.r2.z * m2.r3.y);
	c = (m1.r2.x * m2.r1.z) + (m1.r2.y * m2.r2.z) + (m1.r2.z * m2.r3.z);
	res.r2 = vec3_stack(a, b, c);
	a = (m1.r3.x * m2.r1.x) + (m1.r3.y * m2.r2.x) + (m1.r3.z * m2.r3.x);
	b = (m1.r3.x * m2.r1.y) + (m1.r3.y * m2.r2.y) + (m1.r3.z * m2.r3.y);
	c = (m1.r3.x * m2.r1.z) + (m1.r3.y * m2.r2.z) + (m1.r3.z * m2.r3.z);
	res.r3 = vec3_stack(a, b, c);
	return (res);
}

t_mat3				*mat3_new(t_vec3 r1, t_vec3 r2, t_vec3 r3)
{
	t_mat3			*res;

	res = malloc(sizeof(t_mat3));
	if (res)
	{
		res->r1 = r1;
		res->r2 = r2;
		res->r3 = r3;
	}
	return (res);
}
