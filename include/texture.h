/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:37:42 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/15 16:39:52 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# define PERLIN_XY 512

# include "rt.h"
# include "vector.h"

void				apply_texture(t_ray *r, t_hp *hp, t_geo *geo);

double				get_perlin_noise_pixel(int x, int y);

t_color				compute_uv_texture(t_vec2 st);
t_color				checkerboard_texture(t_vec2 st);
t_vec2				planar_mapping(t_hp hp, t_geo *geo);
t_vec2				sphere_mapping(t_hp hp, t_geo *geo);

t_tex				*init_textures(int type, const char *img_path);
void				test_texture(t_env *e);

#endif
