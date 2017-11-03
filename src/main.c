/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 11:37:25 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/17 16:45:45 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include "geo.h"
#include "ft_printf.h"
#include "light.h"
#include "rtv1.h"
#include "utils.h"

#include <fcntl.h>

void				set_environment(t_env **e)
{
	*e = malloc(sizeof(t_env));
	(*e)->win.width = 0;
	(*e)->win.height = 0;
	(*e)->cam = NULL;
	(*e)->lights = NULL;
	(*e)->geos = NULL;
}

static int			setup_error(int type, t_env *e)
{
	if (type == 0)
		ft_putendl("Usage ./rtv1 [scene.cjson]");
	else if (type == 1)
		ft_putendl("Wrong scene file");
	if (e)
		free(e);
	return (-1);
}

int					main(int ac, char **av)
{
	t_env		*e;

	e = NULL;
	if (ac != 2 || !av[1]) 
		return (setup_error(0, e));
	set_environment(&e);
	if (!(cson_parse(open(av[1], O_RDONLY), e)))
		return (setup_error(1, e));
	if (!(e = sdl_init(e)))
	{
		ft_printf("Error while initializing SDL\n");
		free(e);
	}
	else
	{
		e->scr = set_screen(e->win, e->cam);
		cam_matrix(e->cam, *e->cam->pos, vec3_stack(0, 0, 1), \
			vec3_stack(0, 1, 0));
		sdl_render(e);
		sdl_stop(e);
		free_env(&e);
	}
	return (0);
}
