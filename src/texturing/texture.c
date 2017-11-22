/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:44:36 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/22 06:59:14 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "rt.h"
#include "texture.h"

#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

static Uint32		get_pixel(SDL_Surface *surface, int x, int y)
{
	int				bpp;
	Uint8			*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return *p;
	if (bpp == 2)
		return *(Uint16 *)p;
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	if (bpp == 4)
		return (*(Uint32 *)p);
	return 0;
}

t_color				get_image_px(t_vec2 st, SDL_Surface *tex)
{
	t_color			c;
	int				i;
	unsigned char	*px;

	c = color_new_stack(0., 0., 0., 0.);
	i = (st.x * st.y * tex->w * tex->h) * tex->format->BytesPerPixel;
	px = tex->pixels;
	c.r = px[i];
	c.g = px[i + 1];
	c.b = px[i + 2];
	if (tex->format->BytesPerPixel == 4)
		c.a = px[i + 3];
	else
		c.a = 255.;
	return (c);
}

void				apply_texture(t_ray *r, t_hp *hp, t_geo *geo, t_env *e)
{
	Uint32			col;

	e->tex->uv = sphere_mapping(*hp, geo);
	col = get_pixel(e->tex->curr, e->tex->uv.x * e->tex->curr->w, \
		e->tex->uv.y * e->tex->curr->h);
	if (e->tex->type == 1)
	{
		r->color = color_new_stack((col) & 0xff, \
			(col >> 8) & 0xff, \
			(col >> 16) & 0xff, 255.);
		color_div_fac(&(r->color), 255);
	}
	else if (e->tex->type == 2)
	{
		hp->normal.x = ((col) & 0xff) / 255.;
		hp->normal.y = ((col >> 8) & 0xff) / 255.;
		hp->normal.z = ((col >> 16) & 0xff) / 255.;
	}
}

t_tex				*init_textures(int type, const char *img_path)
{
	t_tex			*tex;
	SDL_Surface		*px;

	if (!(px = STBIMG_Load(img_path)))
	{
		ft_printf("Failed to load image: %s\n", img_path);
		return (NULL);
	}
	tex = malloc(sizeof(t_tex));
	tex->type = type;
	tex->uv = vec2_stack(0., 0.);
	tex->curr = px;
	return (tex);
}
