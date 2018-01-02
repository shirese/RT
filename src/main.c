/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 11:37:25 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/28 13:35:36 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "cson_parser.h"
#include "geo.h"
#include "ft_printf.h"
#include "light.h"
#include "rt.h"
#include "sdl_func.h"
#include "texture.h"
#include "utils.h"

#include <fcntl.h>

static int				setup_error(int type, t_env *e)
{
	if (type == 0)
		ft_putendl("Usage ./rt [scene.cjson]");
	else if (type == 1)
		ft_putendl("Wrong scene file");
	if (e)
		free(e);
	return (-1);
}

/*
** static void				add_neg_geos(t_env *e)
** {
** t_geo *g;
**
** g = NULL;
** g = new_cylinder(vec3_new(0., 0.2, -1.5), vec3_stack(0.0, 0., 1.), 0.3);
** add_geo_coeff(g, color_new_stack(0.2, 0.8, 0.1), \
** color_new_stack(0.5, 0.5, 0.5), 1.0);
** if (g)
** {
** add_geometry_negative(e->geos, 0, g);
** }
** g = new_sphere(vec3_new(0., -1.0, -1.0), 0.5);
** add_geo_coeff(g, color_new_stack(0.2, 0.8, 0.1), \
** color_new_stack(0.5, 0.5, 0.5), 1.0);
** if (g)
** {
** add_geometry_negative(e->geos, 0, g);
** }
** g = new_sphere(vec3_new(0., -1.0, -3.0), 0.5);
** add_geo_coeff(g, color_new_stack(0.2, 0.8, 0.1), \
** color_new_stack(0.5, 0.5, 0.5), 1.0);
** if (g)
** {
** add_geometry_negative(e->geos, 0, g);
** }
** }
*/

int						main(int ac, char **av)
{
	t_env		*e;
	t_geo		*g;

	e = NULL;
	g = NULL;
	if (ac != 2 || !av[1])
		return (setup_error(0, e));
	init_environment(&e);
	if (!(cson_parse(open(av[1], O_RDONLY), e)))
		return (setup_error(1, e));
	if (!sdl_init(&e))
		ft_printf("Error while initializing SDL\n");
	else
	{
		e->scr = set_screen(e->win, e->cam);
		e->img = malloc(sizeof(t_color) * e->scr.nx * e->scr.ny);
		cam_matrix(e->cam, *e->cam->pos, vec3_stack(0, 0, 1), \
			vec3_stack(0, 1, 0));
		sdl_render(e);
		sdl_stop(e);
	}
	free_env(&e);
	return (0);
}
