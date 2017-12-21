/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:51:56 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/19 11:20:18 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrice.h"
#include "rt.h"
#include "vector.h"

t_vec3				rotate_stack(t_vec3 vec3, t_mat3 mat)
{
	t_vec3			res;

	res.x = mat.r1.x * vec3.x + mat.r1.y * vec3.y + mat.r1.z * vec3.z;
	res.y = mat.r2.x * vec3.x + mat.r2.y * vec3.y + mat.r2.z * vec3.z;
	res.z = mat.r3.x * vec3.x + mat.r3.y * vec3.y + mat.r3.z * vec3.z;
	return (res);
}

void				rotate(t_vec3 *v, t_mat3 mat)
{
	v->x = mat.r1.x * v->x + mat.r1.y * v->y + mat.r1.z * v->z;
	v->y = mat.r2.x * v->x + mat.r2.y * v->y + mat.r2.z * v->z;
	v->z = mat.r3.x * v->x + mat.r3.y * v->y + mat.r3.z * v->z;
}

t_ray				rotate_ray(t_ray *r, t_mat3 mat)
{
	t_ray			ret;

	ret = *r;
	ret.origin = rotate_stack(ret.origin, mat);
	ret.direction = rotate_stack(r->direction, mat);
	return (ret);
}

t_vec3				rotate_cam(t_vec3 vec3, t_mat3 mat)
{
	t_vec3		res;

	res.x = mat.r1.x + vec3.x * mat.r1.y + vec3.y * mat.r1.z;
	res.y = mat.r2.x + vec3.x * mat.r2.y + vec3.y * mat.r2.z;
	res.z = mat.r3.x + vec3.x * mat.r3.y + vec3.y * mat.r3.z;
	return (res);
}

void				ft_translate(t_vec3 *vec3, t_vec3 trs)
{
	*vec3 = vec3_add_stack(*vec3, trs);
}
