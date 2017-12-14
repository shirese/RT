/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:51:11 by fgallois          #+#    #+#             */
/*   Updated: 2017/12/14 13:17:18 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"

t_vec3			usual_norm(t_geo *geo, t_hp hp)
{
	if (geo->type == 2)
		return (cone_normal(geo, hp.p));
	else if (geo->type == 3)
		return (cylinder_norm(geo, hp));
	else if (geo->type == 4)
		return (sphere_norm(geo, hp));
	return (vec3_stack(0.0, 0.0, 0.0));
}
