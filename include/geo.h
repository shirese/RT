/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 16:12:49 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/21 16:29:43 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEO_H
# define GEO_H

# include "rt.h"
# include "ray.h"
# include "vector.h"

typedef struct	s_cone
{
	t_vec3		axis;
	double		angle;
}				t_cone;

typedef struct	s_cylinder
{
	double		radius;
	t_vec3		axis;
	t_vec3		normal;
}				t_cylinder;

typedef struct	s_plane
{
	t_vec3		normal;
}				t_plane;

typedef struct	s_sphere
{
	double		radius;
}				t_sphere;

typedef struct	s_parallelog
{
	t_vec3		direction1;
	t_vec3		direction2;
}				t_parallelog;

typedef struct	s_disk
{
	t_vec3		normal;
	double		radius;
}				t_disk;

typedef struct	s_paraboloid
{
	double			facta;
	double			factb;
	double			height;
}					t_paraboloid;

void				add_geometry(t_geo *geo, t_geo **geos);
void				parse_geo_attributes(char **line, char *v, \
t_geo *geo, int *fd);
void				parse_geo_attributes_2(char **line, char *v, \
t_geo *geo, int *fd);
t_vec3				cone_normal(t_geo *geo, t_vec3 p);
double				beta2_cone(double expr, double n, double angle);
double				beta_cone(double expr, double n, double a, double o);
double				alpha2_cone(double expr, double n, double angle);
double				alpha_cone(double expr, double n, double dir);

t_hp				(*g_get_obj_collider(int id))(t_geo *geo, t_ray *r);
t_hp				hit_cone(t_geo *geo, t_ray *r);
t_hp				hit_cylinder(t_geo *geo, t_ray *r);
t_hp				hit_paraboloid(t_geo *geo, t_ray *r);
t_hp				hit_plane(t_geo *geo, t_ray *r);
t_hp				hit_sphere(t_geo *geo, t_ray *r);
t_hp				hit_disk(t_geo *geo, t_ray *r);

int					malloc_geo(void **type, int size, int geo_id, t_geo **geo);
int					belong_to_paraboloid(t_geo *geo, t_vec3 pos);

int					belong_to(t_geo *g, t_vec3 pos);
int					belong_to_cone(t_geo *geo, t_vec3 pos);
int					belong_to_cylinder(t_geo *geo, t_vec3 pos);
int					belong_to_disk(t_geo *geo, t_vec3 pos);
int					belong_to_sphere(t_geo *geo, t_vec3 pos);
int					belong_to_plane(t_geo *geo, t_vec3 pos);
int					register_cut(t_geo *geo, int *fd, char **line, char *v);
t_geo				*new_cone(t_vec3 *position, t_vec3 axis, double angle);
t_geo				*new_cylinder(t_vec3 *position, t_vec3 axis, double radius);
t_geo				*new_disk(t_vec3 *position, t_vec3 normal, double radius);
t_geo				*new_paraboloid(t_vec3 *position, double a, double b);
t_geo				*new_plane(t_vec3 *position, t_vec3 normal);
t_geo				*new_sphere(t_vec3 *position, double radius);
void				print_geo(t_geo *geo);
void				cone_solutions(t_geo *geo, t_ray *r, t_hp *sol);
void				cylinder_solutions(t_geo *geo, t_ray *r, t_hp *sol);
void				sphere_solutions(t_geo *geo, t_ray *r, t_hp *sol);
t_vec3				cut_norm(t_geo *geo, t_hp hp);
t_vec3				cylinder_norm(t_geo *geo, t_hp hp);
t_vec3				sphere_norm(t_geo *geo, t_vec3 pos);
t_vec3				disk_norm(t_geo *geo);
t_vec3				para_norm(t_geo *geo, t_vec3 hp);
t_vec3				plane_norm(t_geo *geo);

/*
** CUT
*/

void				print_cut(t_geo *geo);
double				distance_from_hp1(t_ray *r, t_geo *geo, t_hp hp_1, t_hp hp_2);
int					is_cut(t_geo *geo);
int					is_on_cut(t_cut *cut, t_hp hp);
int					belong_after_cut(t_geo *geo, t_hp hp);
t_hp				first_in_cut(t_geo *geo, t_ray *r, t_hp hp_1, t_hp hp_2);
t_hp				hit_and_cut(t_geo *geo, t_hp hp_1, t_hp hp_2, t_ray *r);
t_vec3				normal_cut(t_geo *geo, t_hp hp);
t_vec3				negative_norm(t_geo *geo, t_hp hp);
void				fill_solution_cylinder(t_geo *geo, t_ray *r, double *abcd, t_hp *sol);
void				fill_solution_disk(t_geo *geo, t_ray *r, double *expr, t_hp *sol);

/*
** NEGATIVE
*/

int					is_geo_dug(t_geo *geo);
int					is_scene_dug(t_geo *geo);
int					add_geometry_negative(t_geo *geo, int i, t_geo *neg0);
t_hp				first_outside_neg(t_geo *geo, t_ray *r, t_hp *sol_geo);
t_hp				is_touched_by_neg(t_geo *geo, t_ray *r, t_hp sol_geo);
int					set_borns_neg(t_geo *geo, t_ray *r);

#endif
