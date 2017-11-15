/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:44:36 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/15 12:29:01 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <imago2.h>

#include "color.h"
#include "ft_printf.h"
#include "rt.h"
#include "texture.h"

#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

t_color				get_image_px(t_vec2 st, SDL_Surface *tex)
{
	t_color			c;
	int				i;
	unsigned char	*px;

	c = color_new_stack(0., 0., 0., 0.);
	// i = (st.x * st.y * w * h) * 4;
	i = (st.x * st.y * tex->w * tex->h) * tex->format->BytesPerPixel;
	px = tex->pixels;
	c.r = px[i];
	c.g = px[i + 1];
	c.b = px[i + 2];
	if (tex->format->BytesPerPixel == 4)
		c.a = px[i + 3];
	else
		c.a = 255.;
	// printf("[%f %f %f %f]\n", c.r, c.g, c.b, c.a);
	return (c);
}

SDL_Surface			*init_textures(const char *img_path, t_env *e)
{
	SDL_Surface		*px;

	if (!(px = STBIMG_Load(img_path)))
	{
		printf("Failed to load image: %s\n", img_path);
		return (NULL);
	}
	// if (!(px = img_load_pixels(img_path, &width, &height, IMG_FMT_RGBA32)))
	// {
	// 	printf("Failed to load image: %s\n", img_path);
	// 	return (NULL);
	// }
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
	return (px);
}

// void				test_texture(t_env *e)
// {
// 	SDL_RenderCopy(e->win.rend, e->tex, NULL, NULL);
// 	SDL_UpdateWindowSurface(e->win.handle);
// 	SDL_RenderPresent(e->win.rend);
// }

void				apply_texture(t_ray *r, t_hp hp, t_geo *geo, t_env *e)
{
	t_vec2			uv;
	Uint32			col;

	uv = sphere_mapping(hp, geo);
	col = getpixel(e->tex, uv.x * e->tex->w, uv.y * e->tex->h);
	// uv = planar_mapping(hp, geo);

	r->color = color_new_stack(col, col >> 8, col >> 16, 255.);
	// r->color = get_image_px(uv, e->tex);
	// r->color = get_image_px(uv, e->tex->width, e->tex->height, e->tex->px);
}
