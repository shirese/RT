/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 17:36:26 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/17 11:18:01 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H

# define LIGHT_H

# include "rt.h"

typedef struct		s_ambient
{
	int				toto;
}					t_ambient;

typedef struct		s_directional
{
	t_vec3			*dir;
}					t_directional;

typedef struct		s_spot
{
	t_vec3			*pos;
}					t_spot;

int					assign_light(int type, t_light **light);
int					parse_light_colors(char *value, t_light **light);
int					parse_light_direction(char *value, t_light **light);
int					parse_light_position(char *value, t_light **light);

void				apply_lights(t_ray *r, t_geo *geo, t_hp hp, t_env *e);
t_color				calc_ambient(t_light *light);
t_color				color_new_stack(double r, double g, double b, double a);
t_color				*color_new(double r, double g, double b, double a);
t_light				*generate_lights(void);

t_vec3				vec3_reflection(void *l, t_hp hp);

void				add_light(t_light *light, t_light **lights);
int					setup_light(t_light **light);

void				shade_phong(t_mater *mater, t_hp hp, t_light *l, t_ray *r);

#endif