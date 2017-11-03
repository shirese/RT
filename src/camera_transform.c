/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 16:11:36 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/13 16:18:00 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				cam_rot_x(t_mat4 *cam_matrix, double angle)
{
	double			rad;
	t_vec3			up;
	t_vec3			dir;

	rad = angle;
	up = vec3_stack(cam_matrix->r2.x, cam_matrix->r2.y, cam_matrix->r2.z);
	dir = vec3_stack(cam_matrix->r3.x, cam_matrix->r3.y, cam_matrix->r3.z);
	cam_matrix->r2.x += dir.x * (-angle);
	cam_matrix->r2.y += dir.y * (-angle);
	cam_matrix->r2.z += dir.z * (-angle);
	cam_matrix->r3.x += up.x * angle;
	cam_matrix->r3.y += up.y * angle;
	cam_matrix->r3.z += up.z * angle;
	cam_matrix->r2 = vec4_normalize_stack(cam_matrix->r2);
	cam_matrix->r3 = vec4_normalize_stack(cam_matrix->r3);
}

void				cam_rot_y(t_mat4 *cam_matrix, double angle)
{
	double			rad;
	t_vec3			left;
	t_vec3			dir;

	rad = angle;
	left = vec3_stack(cam_matrix->r1.x, cam_matrix->r1.y, cam_matrix->r1.z);
	dir = vec3_stack(cam_matrix->r3.x, cam_matrix->r3.y, cam_matrix->r3.z);
	cam_matrix->r1.x += dir.x * (-angle);
	cam_matrix->r1.y += dir.y * (-angle);
	cam_matrix->r1.z += dir.z * (-angle);
	cam_matrix->r3.x += left.x * angle;
	cam_matrix->r3.y += left.y * angle;
	cam_matrix->r3.z += left.z * angle;
	cam_matrix->r1 = vec4_normalize_stack(cam_matrix->r1);
	cam_matrix->r3 = vec4_normalize_stack(cam_matrix->r3);
}

void				cam_rot_z(t_mat4 *cam_matrix, double angle)
{
	double			rad;
	t_vec3			left;
	t_vec3			up;

	rad = angle;
	left = vec3_stack(cam_matrix->r1.x, cam_matrix->r1.y, cam_matrix->r1.z);
	up = vec3_stack(cam_matrix->r2.x, cam_matrix->r2.y, cam_matrix->r2.z);
	cam_matrix->r1.x += up.x * angle;
	cam_matrix->r1.y += up.y * angle;
	cam_matrix->r1.z += up.z * angle;
	cam_matrix->r2.x += left.x * (-angle);
	cam_matrix->r2.y += left.y * (-angle);
	cam_matrix->r2.z += left.z * (-angle);
	cam_matrix->r1 = vec4_normalize_stack(cam_matrix->r1);
	cam_matrix->r2 = vec4_normalize_stack(cam_matrix->r2);
}

t_mat4				*setup_camera_rotation(double x, double y, double z)
{
	t_vec4			v;
	t_mat3			mat_rot;
	t_mat4			*cam_to_world;

	v = vec4_stack(0.0, 0.0, 0.0, 0.0);
	cam_to_world = mat4_new(v, v, v, v);
	if (cam_to_world)
	{
		mat_rot = mat3_rot_stack(x, y, z);
		cam_to_world->r1.x = mat_rot.r1.x;
		cam_to_world->r1.y = mat_rot.r1.y;
		cam_to_world->r1.z = mat_rot.r1.z;
		cam_to_world->r1.w = 0;
		cam_to_world->r2.x = mat_rot.r2.x;
		cam_to_world->r2.y = mat_rot.r2.y;
		cam_to_world->r2.z = mat_rot.r2.z;
		cam_to_world->r2.w = 0;
		cam_to_world->r3.x = mat_rot.r3.x;
		cam_to_world->r3.y = mat_rot.r3.y;
		cam_to_world->r3.z = mat_rot.r1.z;
		cam_to_world->r3.w = 0;
	}
	return (cam_to_world);
}

void				cam_matrix(t_cam *cam, t_vec3 pos, t_vec3 look, t_vec3 up)
{
	t_vec4			v;
	t_vec3			dir;
	t_vec3			left;

	if (!cam->cam_to_world)
	{
		v = vec4_stack(0.0, 0.0, 0.0, 1.0);
		cam->cam_to_world = mat4_new(v, v, v, v);
	}
	dir = vec3_normalize_stack(vec3_sub_stack(pos, look));
	left = vec3_normalize_stack(vec3_cross_prod_stack(vec3_normalize_stack(up),\
		dir));
	up = vec3_cross_prod_stack(dir, left);
	cam->cam_to_world->r1.x = left.x;
	cam->cam_to_world->r1.y = left.y;
	cam->cam_to_world->r1.z = left.z;
	cam->cam_to_world->r2.x = up.x;
	cam->cam_to_world->r2.y = up.y;
	cam->cam_to_world->r2.z = up.z;
	cam->cam_to_world->r3.x = dir.x;
	cam->cam_to_world->r3.y = dir.y;
	cam->cam_to_world->r3.z = dir.z;
	cam->cam_to_world->r4.x = cam->pos->x;
	cam->cam_to_world->r4.y = cam->pos->y;
	cam->cam_to_world->r4.z = cam->pos->z;
}
