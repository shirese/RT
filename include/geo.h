/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:12:49 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/18 17:27:02 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEO_H
# define GEO_H

# include "rt.h"
# include "ray.h"
# include "vector.h"

typedef struct		s_cone
{
	t_vec3			axis;
	double			angle;
}					t_cone;

typedef struct		s_cylinder
{
	double			radius;
	t_vec3			axis;
	t_vec3			normal;
}					t_cylinder;

typedef struct		s_plane
{
	t_vec3			normal;
}					t_plane;

typedef struct		s_sphere
{
	double			radius;
}					t_sphere;

typedef struct 	s_parallelog
{
	t_vec3			direction1;
	t_vec3			direction2;	
}					t_parallelog;

typedef struct 		s_disk
{
	t_vec3			normal;
	double 			radius;
}					t_disk;

void				add_geometry(t_geo *geo, t_geo **geos);
int					add_disk(int *fd, char **line, t_env *e);
void				parse_geo_attributes(char *line, char *value, t_geo *geo);

t_vec3				cone_normal(t_geo *geo, t_cone *c, t_vec3 p);
double				beta2_cone(double expr, double n, double angle);
double				beta_cone(double expr, double n, double a, double o);
double				alpha2_cone(double expr, double n, double angle);
double				alpha_cone(double expr, double n, double dir);

t_hp				(*g_get_obj_collider(int id))(t_geo *geo, t_ray r);
t_hp				hit_cone(t_geo *geo, t_ray r);
t_hp				hit_cylinder(t_geo *geo, t_ray r);
t_hp				hit_plane(t_geo *geo, t_ray r);
t_hp				hit_sphere(t_geo *geo, t_ray r);
t_hp				hit_disk(t_geo *geo, t_ray r);

int					malloc_geo(void **type, int size, int geo_id, t_geo **geo);

#endif