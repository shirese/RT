/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:40:36 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/12 12:21:48 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "light.h"
#include "rt.h"
#include "utils.h"

int					parse_light_colors(char *value, t_light **light)
{
	color_set(color_new_stack(ft_atof_cson(&value), ft_atof_cson(&value), \
			ft_atof_cson(&value), ft_atof_cson(&value)), (*light)->color);
	if ((*light)->color)
		return (0);
	return (1);
}

int					parse_light_direction(char *value, t_light **l)
{
	if ((*l)->type == 2)
	{
		vec3_set(ft_atof_cson(&value), ft_atof_cson(&value), \
		ft_atof_cson(&value), ((t_directional *)((*l)->curr))->dir);
		return (0);
	}
	return (1);
}

int					parse_light_position(char *value, t_light **l)
{
	if ((*l)->type == 3)
	{
		vec3_set(ft_atof_cson(&value), ft_atof_cson(&value), \
		ft_atof_cson(&value), ((t_point *)((*l)->curr))->pos);
		return (0);
	}
	return (1);
}

int					assign_light(int type, t_light **light)
{
	(*light)->curr = NULL;
	if (type == 1)
		(*light)->type = 1;
	else if (type == 2)
	{
		(*light)->type = 2;
		(*light)->curr = (void *)malloc(sizeof(t_directional));
		((t_directional *)(*light)->curr)->dir = vec3_new(0., 0., 0.);
	}
	else if (type == 3)
	{
		(*light)->type = 3;
		(*light)->curr = (void *)malloc(sizeof(t_point));
		((t_point *)(*light)->curr)->pos = vec3_new(0., 0., 0.);
	}
	else
		return (1);
	return (0);
}
