/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:33:43 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/19 12:17:57 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	float	rez;
	float	fact;
	int		dot_seen;

	rez = 0;
	fact = 1;
	dot_seen = 0;
	while (*str == ' ')
		str++;
	if ((*str == '-' || *str == '+') && str++)
		fact = *str == '-' ? -1 : 1;
	while ((ft_isdigit(*str) || *str == '.') && *str != '\0')
	{
		if (dot_seen == 0 && *str == '.')
			dot_seen = 1;
		else if (ft_isdigit(*str))
		{
			if (dot_seen)
				fact /= 10.0f;
			rez = rez * 10.0f + (float)(*str - '0');
		}
		str++;
	}
	return (rez * fact);
}
