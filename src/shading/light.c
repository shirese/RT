/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 15:31:04 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/21 15:52:19 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "light.h"
#include "rt.h"
#include "vector.h"

t_vec3				get_light_pos(t_vec3 from, t_light *l)
{
	t_vec3			light_pos;

	if (l->type == 2)
		light_pos = vec3_sub_stack(get_light_dir(from, l), from);
	else if (l->type == 3)
		light_pos = *((t_point *)l->curr)->pos;
	else
		light_pos = vec3_stack(0., 0., 0.);
	return (light_pos);
}

t_vec3				get_light_dir(t_vec3 from, t_light *to_light)
{
	t_vec3			light_dir;

	if (to_light->type == 2)
	{
		light_dir = *((t_directional *)to_light->curr)->dir;
		vec3_rev(&light_dir);
		vec3_mult_fact(&light_dir, LIGHT_DIR_DIST);
	}
	else if (to_light->type == 3)
		light_dir = vec3_sub_stack(*((t_point *)to_light->curr)->pos, from);
	else
		light_dir = vec3_stack(0., 0., 0.);
	return (light_dir);
}

t_vec3				vec3_reflection(t_vec3 pos, t_hp hp)
{
	t_vec3			i;
	t_vec3			n;
	t_vec3			r;

	i = vec3_sub_stack(pos, hp.p);
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
	(*light)->color = color_new(0.0, 0.0, 0.0);
	(*light)->type = 0;
	(*light)->next = NULL;
	return (1);
}
