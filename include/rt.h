/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 11:29:42 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/27 10:23:21 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <SDL.h>
# include "matrice.h"
# include "vector.h"
# include "time.h"

# define EPSILON 0.000001
# define FLT_MAX 3.402823e+38
# define INV_PI 0.31830988618379067154
# define INV2_PI 0.15915494309189533577
# define MAX_RECURSION 4
# define WIN_TITLE "Raytracer v0.2"

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

/*
**	RAY TYPE 1- Primary 2- Shadow 3- Refr/Refl
*/
typedef struct		s_ray
{
	int				type;
	t_vec3			origin;
	t_vec3			dir;
	t_color			color;
	double			ior;
	int				rec;
}					t_ray;

typedef struct		s_cut
{
	t_vec3			cut_normal;
	t_vec3			cut_position;
}					t_cut;

typedef struct		s_hit_point
{
	double			t;
	t_vec3			p;
	t_vec3			normal;
	double			ior;
}					t_hp;

/*
**	ILLUM TYPE 1- Diffuse 2- Relexion 3- Refraction
**	4- Reflexion + Refraction
*/
typedef struct		s_mater
{
	t_color			kd;
	t_color			ks;
	int				illum;
	double			ior;
	double			ns;
	double			reflectivity;
	double			transparency;
}					t_mater;

/*
**	TYPE 1- Image 2- Normal map 3- Checkerboard 4- Perlin 5- Transparent
*/
typedef struct		s_tex
{
	int				type;
	t_vec2			uv;
	SDL_Surface		*curr;
}					t_tex;

typedef struct		s_inter
{
	double			t_start;
	double			t_end;
}					t_inter;

/*
**	TYPE 1- Plane 2- Cone 3- Cylinder 4- Sphere
**	SHADER TYPE 1- Phong 2- Toon
*/

typedef struct s_geo	t_geo;
struct				s_geo
{
	int				type;
	int				shader_type;
	void			*curr;
	t_vec3			*origin;
	t_mat3			*rotation;
	t_mater			*mater;
	t_hp			(*is_hit)(t_geo *geo, t_ray *r);
	t_tex			*tex;
	t_geo			*neg;
	t_inter			*borns_neg;
	t_geo			*next;
	t_cut			*cut;
	int				nb_cut;
};
/*
**	The camera matrix is a 4x4 matrix with
**	r1 = axis x,
**	r2 = axis y,
**	r3 = axis z,
**	r4 = cam pos
*/
typedef struct		s_cam
{
	t_vec3			*pos;
	t_mat4			*cam_to_world;
	double			fov;
}					t_cam;

/*
**	TYPE 1- Ambient 2- Directional 3- Pointlight
*/
typedef struct s_light	t_light;

struct				s_light
{
	int				type;
	void			*curr;
	t_color			*color;
	t_light			*next;
	t_light			*last;
};

typedef struct		s_win
{
	SDL_Window		*handle;
	SDL_Renderer	*rend;
	int				w;
	int				h;
}					t_win;

typedef struct		s_screen
{
	int				nx;
	int				ny;
	double			asp_ratio;
	double			scale;
	t_vec3			low_left_corner;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			color;
}					t_screen;

/*
**	A sample rate of 4x is equal to double sample in X and Y
*/
typedef struct		s_env
{
	t_color			*img;
	unsigned int	filter;
	unsigned int	samp_rate;
	t_win			win;
	t_screen		scr;
	t_ray			ray;
	t_cam			*cam;
	t_geo			*geos;
	t_light			*lights;
}					t_env;

int					get_next_line(int const fd, char **line);

t_color				get_px_col(int x, int y, t_env *e);
t_color				find_ray_color(double x, double y, t_env *e);
void				raytrace(t_env *e);

void				set_background(t_env *e);
t_screen			set_screen(t_win win, t_cam *cam);

t_mat4				*setup_camera_rotation(double x, double y, double z);
void				cam_matrix(t_cam *cam, t_vec3 pos, t_vec3 look, t_vec3 up);
int					setup_camera(t_cam **cam);

t_ray				rotate_ray(t_ray *r, t_mat3 mat);
t_vec3				rotate_stack(t_vec3 vec3, t_mat3 mat);
void				rotate(t_vec3 *v, t_mat3 mat);
void				cam_rot_x(t_mat4 *cam_matrix, double angle);
void				cam_rot_y(t_mat4 *cam_matrix, double angle);
void				cam_rot_z(t_mat4 *cam_matrix, double angle);
void				cam_matrix(t_cam *cam, t_vec3 pos, t_vec3 look, t_vec3 up);
void				ft_translate(t_vec3 *vec, t_vec3 trs);

double				deg_to_rad(double deg);
double				clamp(double x, double up, double low);
double				max(double i, double j);

void				fresnel(t_ray r, t_hp hp, double n, double *krefl);
double				coeff_fresnel(t_ray r, t_hp hp, t_geo *geo);
double				find_krefl(t_geo *geo, t_hp hp, t_ray r);
double				find_ior(t_geo *geo, t_ray r, t_hp hp);
double				ior_at_point(t_geo *geo, t_vec3 pos);
double				ior_at_point2(t_geo *g, t_vec3 pos);
void				add_geo_coeff(t_geo *geo, t_color kd,t_color ks, double ior);

#endif
