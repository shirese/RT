/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:54:27 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/08 09:50:28 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*strchr;

	strchr = (char*)s;
	while (*strchr != '\0' && *strchr != c)
		strchr++;
	if (*strchr != c)
		return (NULL);
	return (strchr);
}
