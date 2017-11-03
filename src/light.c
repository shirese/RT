/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 15:31:04 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/13 16:15:13 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "light.h"
#include "rtv1.h"
#include "vector.h"

t_vec3				vec3_reflection(void *l, t_hp hp)
{
	t_spot			*s;
	t_vec3			i;
	t_vec3			n;
	t_vec3			r;

	s = l;
	i = vec3_sub_stack(*s->pos, hp.p);
	n = hp.normal;
	r = vec3_mult_stack(n, 2 * vec3_dot(i, n));
	r = vec3_sub_stack(i, r);
	vec3_normalize(&r);
	return (r);
}

void				add_light(t_light *light, t_light **lights)
{
	t_light			*tmp;

	if (!*lights)
		*lights = light;
	else
	{
		tmp = *lights;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = light;
		(*lights)->last = light;
	}
}

int					setup_light(t_light **light)
{
	*light = malloc(sizeof(t_light));
	if (!*light)
		return (0);
	(*light)->last = *light;
	(*light)->color = color_new(0.0, 0.0, 0.0, 0.0);
	(*light)->type = 0;
	(*light)->next = NULL;
	return (1);
}
