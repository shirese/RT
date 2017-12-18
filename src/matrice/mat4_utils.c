/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:23:18 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/15 11:24:09 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrice.h"
#include "vector.h"

t_vec3				mat4_mult_vec3(t_mat4 m, t_vec3 v)
{
	t_vec3			res;

	res.x = m.r1.x * v.x + m.r1.y * v.y + m.r1.z * v.z + m.r1.w;
	res.y = m.r2.x * v.x + m.r2.y * v.y + m.r2.z * v.z + m.r2.w;
	res.z = m.r3.x * v.x + m.r3.y * v.y + m.r3.z * v.z + m.r3.w;
	return (res);
}
