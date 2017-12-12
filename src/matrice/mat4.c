/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:57:16 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/12 16:29:37 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrice.h"
#include "vector.h"
#include <stdio.h>

t_vec3				mat4_mult_vec3(t_mat4 m, t_vec3 v)
{
	t_vec3			res;

	res.x = m.r1.x * v.x + m.r1.y * v.y + m.r1.z * v.z + m.r1.w;
	res.y = m.r2.x * v.x + m.r2.y * v.y + m.r2.z * v.z + m.r2.w;
	res.z = m.r3.x * v.x + m.r3.y * v.y + m.r3.z * v.z + m.r3.w;
	return (res);
}

t_mat4				mat4_transf(t_vec4 t, t_vec4 r)
{
	t_mat3			rot;
	t_mat4			mat;

	rot = mat3_rot_stack(r.x, r.y, r.z);
	mat.r1.x = rot.r1.x;
	mat.r2.x = rot.r1.y;
	mat.r3.x = rot.r1.z;
	mat.r1.y = rot.r2.x;
	mat.r2.y = rot.r2.y;
	mat.r3.y = rot.r2.z;
	mat.r1.z = rot.r3.x;
	mat.r2.z = rot.r3.y;
	mat.r3.z = rot.r3.z;
	mat.r1.w = t.x;
	mat.r2.w = t.y;
	mat.r3.w = t.z;
	mat.r4.x = 0.;
	mat.r4.y = 0.;
	mat.r4.z = 0.;
	mat.r4.w = 1.;
	return (mat);
}

static void			mat4_mult_norme(t_mat4 *m1, t_mat4 m2)
{
	double			a;
	double			b;
	double			c;
	double			d;

	a = (m1->r3.x * m2.r1.x) + (m1->r3.y * m2.r2.x) + (m1->r3.z * m2.r3.x) + \
		(m1->r3.w * m2.r4.x);
	b = (m1->r3.x * m2.r1.y) + (m1->r3.y * m2.r2.y) + (m1->r3.z * m2.r3.y) + \
		(m1->r3.w * m2.r4.y);
	c = (m1->r3.x * m2.r1.z) + (m1->r3.y * m2.r2.z) + (m1->r3.z * m2.r3.z) + \
		(m1->r3.w * m2.r4.z);
	d = (m1->r3.x * m2.r1.w) + (m1->r3.y * m2.r2.w) + (m1->r3.z * m2.r3.w) + \
		(m1->r3.w * m2.r4.w);
	m1->r3 = vec4_stack(a, b, c, d);
	a = (m1->r4.x * m2.r1.x) + (m1->r4.y * m2.r2.x) + (m1->r4.z * m2.r3.x) + \
		(m1->r4.w * m2.r4.x);
	b = (m1->r4.x * m2.r1.y) + (m1->r4.y * m2.r2.y) + (m1->r4.z * m2.r3.y) + \
		(m1->r4.w * m2.r4.y);
	c = (m1->r4.x * m2.r1.z) + (m1->r4.y * m2.r2.z) + (m1->r4.z * m2.r3.z) + \
		(m1->r4.w * m2.r4.z);
	d = (m1->r4.x * m2.r1.w) + (m1->r4.y * m2.r2.w) + (m1->r4.z * m2.r3.w) + \
		(m1->r4.w * m2.r4.w);
	m1->r4 = vec4_stack(a, b, c, d);
}

t_mat4				*mat4_mult(t_mat4 *m1, t_mat4 m2)
{
	double			a;
	double			b;
	double			c;
	double			d;

	a = (m1->r1.x * m2.r1.x) + (m1->r1.y * m2.r2.x) + (m1->r1.z * m2.r3.x) + \
		(m1->r1.w * m2.r4.x);
	b = (m1->r1.x * m2.r1.y) + (m1->r1.y * m2.r2.y) + (m1->r1.z * m2.r3.y) + \
		(m1->r1.w * m2.r4.y);
	c = (m1->r1.x * m2.r1.z) + (m1->r1.y * m2.r2.z) + (m1->r1.z * m2.r3.z) + \
		(m1->r1.w * m2.r4.z);
	d = (m1->r1.x * m2.r1.w) + (m1->r1.y * m2.r2.w) + (m1->r1.z * m2.r3.w) + \
		(m1->r1.w * m2.r4.w);
	m1->r1 = vec4_stack(a, b, c, d);
	a = (m1->r2.x * m2.r1.x) + (m1->r2.y * m2.r2.x) + (m1->r2.z * m2.r3.x) + \
		(m1->r2.w * m2.r4.x);
	b = (m1->r2.x * m2.r1.y) + (m1->r2.y * m2.r2.y) + (m1->r2.z * m2.r3.y) + \
		(m1->r2.w * m2.r4.y);
	c = (m1->r2.x * m2.r1.z) + (m1->r2.y * m2.r2.z) + (m1->r2.z * m2.r3.z) + \
		(m1->r2.w * m2.r4.z);
	d = (m1->r2.x * m2.r1.w) + (m1->r2.y * m2.r2.w) + (m1->r2.z * m2.r3.w) + \
		(m1->r2.w * m2.r4.w);
	m1->r2 = vec4_stack(a, b, c, d);
	mat4_mult_norme(m1, m2);
	return (m1);
}

t_mat4				*mat4_new(t_vec4 r1, t_vec4 r2, t_vec4 r3, t_vec4 r4)
{
	t_mat4			*res;

	res = malloc(sizeof(t_mat4));
	if (res)
	{
		res->r1 = r1;
		res->r2 = r2;
		res->r3 = r3;
		res->r4 = r4;
	}
	return (res);
}

t_mat4				mat4_id(void)
{
	t_mat4			res;

	res.r1 = vec4_stack(1., 0., 0., 0.);
	res.r2 = vec4_stack(0., 1., 0., 0.);
	res.r3 = vec4_stack(0., 0., 1., 0.);
	res.r4 = vec4_stack(0., 0., 0., 1.);
	return (res);
}
