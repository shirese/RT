/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thr_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:19:41 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/04 12:20:12 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_multithread.h"

int					find_factor(int n, int f)
{
	int				i;

	i = 0;
	while (i < TILESIZE)
	{
		if (n % (f - i) == 0)
			return (f - i);
		else if (n % (f + i) == 0)
			return (f + i);
		i++;
	}
	return (0);
}
