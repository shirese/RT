/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:37:26 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/09 10:37:12 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "light.h"
#include "utils.h"

void				print_lights(t_env *e)
{
	t_light			*light;

	light = e->lights;
	while (light)
	{
		ft_putstr("\n\n///		LIGHT		////\n\n");
		ft_printf("TYPE 		[%d]\n", light->type);
		ft_putstr("COLOR 		");
		print_color(*light->color);
		if (light->type == 2)
		{
			ft_putstr("DIR 		");
			vec3_print(*((t_directional *)light->curr)->dir);
		}
		if (light->type == 3)
		{
			ft_printf("\nPOS 		[%f %f %f]\n", \
				((t_point *)light->curr)->pos->x,
				((t_point *)light->curr)->pos->y,
				((t_point *)light->curr)->pos->z);
		}
		light = light->next;
	}
}
