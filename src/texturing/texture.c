/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:44:36 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/15 10:55:22 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <imago2.h>

#include "color.h"
#include "ft_printf.h"
#include "rt.h"
#include "texture.h"

t_color				get_image_px(t_vec2 st, int w, int h, unsigned char *px)
{
	t_color			c;
	int				i;

	c = color_new_stack(0., 0., 0., 0.);
	i = ((st.y * h * w) + (st.x * w)) * 4;
	i -= (i % 4);
	c.r = px[i];
	c.g = px[i + 1];
	c.b = px[i + 2];
	c.a = px[i + 3];
	// printf("[%f %f %f %f]\n", c.r, c.g, c.b, c.a);
	return (c);
}

t_tex				*init_textures(const char *img_path)
{
	t_tex			*tex;
	int				width;
	int				height;
	unsigned char	*px;

	if (!(px = img_load_pixels(img_path, &width, &height, IMG_FMT_RGBA32)))
	{
		printf("Failed to load image: %s\n", img_path);
		return (NULL);
	}
	// else
	// {
	// 	for (int i = 0; i < height; i++)
	// 	{
	// 		for (int j = 0; j < width; j++)
	// 		{
	// 			printf("[%d %d %d %d]\n", 
	// 				px[((i * width + j) * 4)],
	// 				px[((i * width + j) * 4 + 1)],
	// 				px[((i * width + j) * 4 + 2)],
	// 				px[((i * width + j) * 4 + 3)]
	// 			);
	// 		}
	// 	}
	// }
	tex = malloc(sizeof(t_tex));
	tex->px = px;
	tex->width = width;
	tex->height = height;
	return (tex);
}

void				apply_texture(t_ray *r, t_hp hp, t_geo *geo, t_env *e)
{
	t_vec2			uv;

	// uv = sphere_mapping(hp, geo);
	uv = planar_mapping(hp, geo);
	r->color = get_image_px(uv, e->tex->width, e->tex->height, e->tex->px);
}
