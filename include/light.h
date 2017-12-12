/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 17:36:26 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/12 14:16:36 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H

# define LIGHT_H

# include "rt.h"

# define LIGHT_DIR_DIST 1E5

typedef struct		s_directional
{
	t_vec3			*dir;
}					t_directional;

typedef struct		s_point
{
	t_vec3			*pos;
}					t_point;

int					assign_light(int type, t_light **light);
int					parse_light_colors(char *value, t_light **light);
int					parse_light_direction(char *value, t_light **light);
int					parse_light_position(char *value, t_light **light);

void				apply_ambient_light(t_ray *r, t_env *e);
void				apply_lights(t_ray *r, t_geo *geo, t_hp hp, t_env *e);

t_vec3				get_light_dir(t_vec3 from, t_light *to_light);
t_vec3				get_light_pos(t_vec3 from, t_light *l);
t_vec3				vec3_reflection(t_vec3 pos, t_hp hp);

void				add_light(t_light *light, t_light **lights);
int					setup_light(t_light **light);

void				shade_phong(t_mater *mater, t_hp hp, t_light *l, t_ray *r);

#endif
