/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:40:36 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/22 12:00:12 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "light.h"
#include "rtv1.h"
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
		((t_directional *)((*l)->curr))->dir = vec3_new(ft_atof_cson(&value), \
			ft_atof_cson(&value), ft_atof_cson(&value));
		return (0);
	}
	return (1);
}

int					parse_light_position(char *value, t_light **light)
{
	t_spot			*spot;

	spot = (*light)->curr;
	if ((*light)->type == 3)
	{
		spot->pos = vec3_new(ft_atof_cson(&value), \
			ft_atof_cson(&value), ft_atof_cson(&value));
		return (0);
	}
	return (1);
}

int					assign_light(int type, t_light **light)
{
	if (type == 1)
	{
		(*light)->type = 1;
		(*light)->curr = (void *)malloc(sizeof(t_ambient));
	}
	else if (type == 2)
	{
		(*light)->type = 2;
		(*light)->curr = (void *)malloc(sizeof(t_directional));
	}
	else if (type == 3)
	{
		(*light)->type = 3;
		(*light)->curr = (void *)malloc(sizeof(t_spot));
	}
	else
		return (1);
	return (0);
}
