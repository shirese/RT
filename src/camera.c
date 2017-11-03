/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 06:17:33 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/13 16:14:08 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrice.h"
#include "rtv1.h"
#include "vector.h"

int					setup_camera(t_cam **cam)
{
	*cam = malloc(sizeof(t_cam));
	if (!*cam)
		return (0);
	(*cam)->pos = vec3_new(0, 0, 0);
	if (!(*cam)->pos)
	{
		free(*cam);
		return (0);
	}
	(*cam)->cam_to_world = NULL;
	(*cam)->fov = 0;
	return (1);
}
