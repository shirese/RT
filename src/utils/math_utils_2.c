/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:13:46 by chaueur           #+#    #+#             */
/*   Updated: 2017/11/10 16:16:35 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double 				lerp(double t, double a, double b) {
	return a + t * (b - a);
}

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
