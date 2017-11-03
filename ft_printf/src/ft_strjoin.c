/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:49:55 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/21 12:25:17 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s_len;
	char		*s_join;

	if (!s1 && s2)
		return (s_join = ft_strdup(s2));
	if (!s2 && s1)
		return (s_join = ft_strdup(s1));
	s_len = ft_strlen(s1) + ft_strlen(s2);
	s_join = ft_strnew(s_len);
	if (s_join == NULL)
		return (NULL);
	s_join = ft_strcpy(s_join, s1);
	s_join = ft_strcat(s_join, s2);
	return (s_join);
}
