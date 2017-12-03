/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:07:50 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/18 10:26:24 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double				positive_smallest(double a, double b)
{
	if (a < 0)
	{
		if (b > 0)
			return (b);
		return (-1);
	}
	if (b < 0)
	{
		if (a > 0)
			return (a);
		return (-1);
	}
	if (a < b)
		return (a);
	return (b);
}

double				non_positive_smallest(double a, double b)
{
	double ps;

	ps = positive_smallest(a, b);
	if (a == ps && b > a)
		return (b);
	else if (b == ps && a > b)
		return (a);
	return (-1.0);
}

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

