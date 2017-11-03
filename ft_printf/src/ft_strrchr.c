/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:05:17 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/10 15:42:22 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	char	*strrchr;

	strrchr = (char*)s;
	strrchr = strrchr + ft_strlen(s);
	chr = (char)c;
	while (*strrchr - 1)
	{
		if (chr == *strrchr)
			return (strrchr);
		strrchr--;
	}
	return (NULL);
}
