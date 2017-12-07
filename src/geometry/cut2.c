/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 13:30:03 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/19 10:53:18 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "geo.h"
#include "ray.h"
#include "rt.h"
#include "utils.h"


void				print_cut(t_geo *geo)
{
	t_cut	*cut;
	int 	i;

	i = 0;
	cut = geo->cut;
	while (i < geo->nb_cut)
	{
		printf("Cut\n\tNormale \n");
		vec3_print(cut[i].cut_normal);
		printf("\tPosition \n");
		vec3_print(cut[i].cut_position);
		printf("\n");
		i++;
	} 
}

/*t_vec3			*get_cut_position(char *line, t_geo *geo, t_vec3 *normal, int *size_cut)
{
	t_vec3		*position;
	char 		*value;

	if (get_next_line(*fd, line) && **line == '\t' && (value = *line + 4))
	{
		if (ft_strncmp(line, "\tcut_position", 13) == 0 && (value += 11))
		{
			position = vec3_new(ft_atof_cson(&value), ft_atof_cson(&value), \
			ft_atof_cson(&value));
			if (!ft_realloc((void *)geo->cut, *size_cut, *size_cut - 1) || !position)
				return (NULL);
			geo->cut[*size_cut - 1].cut_normal = normal;
			geo->cut[*size_cut - 1].cut_normal = position;
		}
		return (NULL);
	}
	return (NULL);
}*/
