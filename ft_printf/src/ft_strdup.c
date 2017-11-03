/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:35:49 by chaueur           #+#    #+#             */
/*   Updated: 2016/12/16 14:46:00 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strdup(const char *s1)
{
	int			index;
	size_t		size;
	char		*str;

	index = 0;
	size = ft_strlen(s1);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	else
	{
		while (s1[index] != '\0')
		{
			str[index] = s1[index];
			index++;
		}
		str[index] = '\0';
	}
	return (str);
}
