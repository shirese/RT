/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 11:55:40 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/10 16:35:32 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include "ft_printf.h"
#include "geo.h"
#include "light.h"
#include "rt.h"
#include "utils.h"

int					parse_geo(int *fd, char **line, t_env *e)
{
	if (ft_strncmp(*line, "cone", 4) == 0)
		return (add_cone(fd, line, e));
	else if (ft_strncmp(*line, "cylinder", 8) == 0)
		return (add_cylinder(fd, line, e));
	else if (ft_strncmp(*line, "plane", 5) == 0)
		return (add_plane(fd, line, e));
	else if (ft_strncmp(*line, "sphere", 6) == 0)
		return (add_sphere(fd, line, e));
	else if (ft_strncmp(*line, "disk", 4) == 0)
		return (add_disk(fd, line, e));
	else if (ft_strncmp(*line, "pipe", 4) == 0)
		return (add_pipe(fd, line, e));
	else if (ft_strncmp(*line, "parahyp", 7) == 0)
		return (add_parahyp(fd, line, e));
	return (7);
}

int					parse_light(int *fd, char **line, t_env *e)
{
	int				err;
	char			*value;
	t_light			*light;

	err = 0;
	value = NULL;
	light = NULL;
	if (!setup_light(&light))
		return (3);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		value = *line + 4;
		if (ft_strncmp(*line, "\ttype", 5) == 0 && (value += 3))
			err = assign_light(ft_atoi(value), &light);
		else if (ft_strncmp(*line, "\tcolor", 6) == 0 && (value += 4))
			err = parse_light_colors(value, &light);
		else if (ft_strncmp(*line, "\tdir", 4) == 0 && (value += 2))
			err = parse_light_direction(value, &light);
		else if (ft_strncmp(*line, "\tpos", 4) == 0 && (value += 2))
			err = parse_light_position(value, &light);
		else
			break ;
	}
	add_light(light, &(e->lights));
	return (0);
}

int					parse_camera(int *fd, char **line, t_env *e)
{
	char			*value;

	value = NULL;
	if (!setup_camera(&(e->cam)))
		return (2);
	while (get_next_line(*fd, line) && **line == '\t')
	{
		value = *line + 4;
		if (!ft_strncmp(*line, "\tpos", 4) && (value += 2))
			vec3_set(ft_atof_cson(&value), ft_atof_cson(&value), \
				ft_atof_cson(&value), e->cam->pos);
		else if (!ft_strncmp(*line, "\trotation", 4) && (value += 7))
			e->cam->cam_to_world = setup_camera_rotation(ft_atof_cson(&value), \
				ft_atof_cson(&value), ft_atof_cson(&value));
		else if (!ft_strncmp(*line, "\tfov", 4) && (value += 2))
			e->cam->fov = ft_atoi(value);
		else
			break ;
	}
	if (e->cam->fov > 0)
		return (0);
	return (2);
}

int					parse_window(int *fd, char **line, t_env *e)
{
	char			*value;

	value = NULL;
	//ft_printf("%s\n", *line);
	while (**line == '\t')
	{
		value = *line + 8;
		if (ft_strncmp(*line, "\twidth", 6) && ft_strncmp(*line, "\theight", 7))
			break ;
		else if (!ft_strncmp(*line, "\twidth", 6))
			e->win.width = ft_atoi(value);
		else if (!ft_strncmp(*line, "\theight", 7) && (value += 1))
			e->win.height = ft_atoi(value);
		get_next_line(*fd, line);
	}
	if ((e->win.width > 0 && e->win.width < 2550))
	{
		if ((e->win.height > 0 && e->win.height < 1440))
			return (0);
	}
	return (1);
}
