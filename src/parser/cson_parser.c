/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 11:19:35 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/17 16:46:13 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include "ft_printf.h"
#include "geo.h"
#include "light.h"
#include "rt.h"
#include "utils.h"

static int			handle_error(int err)
{
	if (err != 0)
	{
		if (err == 1)
			ft_printf("Invalid window\n");
		if (err == 2)
			ft_printf("Invalid camera\n");
		if (err == 3)
			ft_printf("Invalid light\n");
		if (err == 4)
			ft_printf("Invalid geo\n");
		if (err == 5)
			ft_printf("Invalid geo(plane)\n");
		if (err == 6)
			ft_printf("Invalid geo(cone)\n");
		if (err == 7)
			ft_printf("Invalid geo(cylinder)\n");
		if (err == 8)
			ft_printf("Invalid geo(sphere)\n");
		if (err == 9)
			ft_printf("Invalid geo(disk)\n");
		if (err == 10)
			ft_printf("Invalid geo(pipe)\n");
		if (err == 11)
			ft_printf("Invalid geo(parabolide hyperbolique)\n");
		return (1);
	}
	return (0);
}

int					cson_parse(int fd, t_env *e)
{
	char			*line;
	int				err;
	int				i;

	line = NULL;
	err = 0;
	i = 0;
	get_next_line(fd, &line);
	while (*line)
	{
		//ft_putstr(line);
		if (!err && !ft_strncmp(line, "window", 6) && get_next_line(fd, &line))
			err = parse_window(&fd, &line, e);
		if (!err && !ft_strncmp(line, "camera", 6))
			err = parse_camera(&fd, &line, e);
		if (!err && !ft_strncmp(line, "light", 5))
			err = parse_light(&fd, &line, e);
		if (!err && ft_strncmp(line, "light", 5))
			err = parse_geo(&fd, &line, e);
		if (handle_error(err) != 0)
			return (0);
	}
	return (1);
}
