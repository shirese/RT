/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:07:50 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/11 16:59:00 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double				deg_to_rad(double deg)
{
	double			rad;

	rad = deg * M_PI / 180;
	return (rad);
}

double				min(double i, double j)
{
	return (i < j) ? i : j;
}

double				max(double i, double j)
{
	return (i > j) ? i : j;
}

double				clamp(double x, double min, double max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return (x);
}
