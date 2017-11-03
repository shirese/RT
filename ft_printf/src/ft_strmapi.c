/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:27:42 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/11 12:07:04 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int			i;
	int			len;
	int			counter;
	char		*s_new;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	counter = 0;
	s_new = ft_strnew(len);
	if (!s_new)
		return (NULL);
	while (counter < len)
	{
		s_new[counter] = (*f)(i, s[counter]);
		i++;
		counter++;
	}
	return (s_new);
}
