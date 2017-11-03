/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:09:02 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/11 12:07:12 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int			len;
	int			counter;
	char		*s_new;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	counter = 0;
	s_new = ft_strnew(len);
	if (!s_new)
		return (NULL);
	while (counter < len)
	{
		s_new[counter] = (*f)(s[counter]);
		counter++;
	}
	return (s_new);
}
