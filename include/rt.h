/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirese <shirese@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 11:29:42 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/30 18:09:51 by shirese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <SDL.h>
# include "matrice.h"
# include "vector.h"
# include "time.h"

# define WIN_TITLE "Raytracer v0.0"
# define SAVE_PATH "saves/save00"
# define FLT_MAX 3.402823e+38

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	double			a;
}					t_color;

/*
**	RAY TYPE 1- Primary 2- Shadow
*/
typedef struct		s_ray
{
	int				type;
	t_vec3			origin;
	t_vec3			direction;
	t_vec3			point_at_parameter;
	t_color			color;
}					t_ray;

typedef struct		s_hit_point
{
	double			t;
	t_vec3			p;
	t_vec3			normal;
}					t_hp;

typedef struct		s_mater
{
	t_color			kd;
	t_color			ks;
	double			alpha;
}					t_mater;

/*
**	TYPE 1- Plane 2- Cone 3- Cylinder 4- Sphere
*/
typedef struct s_geo	t_geo;
struct				s_geo
{
	int				type;
	void			*curr;
	t_vec3			*origin;
	t_mat3			*rotation;
	t_mater			*mater;
	t_hp			(*is_hit)(t_geo *geo, t_ray r);
	t_geo			*next;
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
**	TYPE 1- Ambient 2- Directional 3- Spotlight
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
	int				width;
	int				height;
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

void				sdl_get_event(SDL_Event event, t_env *e);
void				sdl_draw_point(SDL_Renderer *rend, int x, int y, t_color c);
t_env				*sdl_init(t_env *e);
void				sdl_render(t_env *e);
void				sdl_stop(t_env *e);

#endif
