/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 15:10:12 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/10 15:12:38 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*tmp_s;
	char const	*end;
	char const	*start;

	start = NULL;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (!ft_isblank(*s))
		{
			start = (start == NULL) ? s : start;
			end = s;
		}
		s++;
	}
	if (start == NULL)
		return (ft_strnew(0));
	if ((tmp_s = (char *)malloc(sizeof(char) * (end - start + 2))) == NULL)
		return (NULL);
	s = start;
	while (s <= end)
		*tmp_s++ = *s++;
	*tmp_s = '\0';
	return (tmp_s - (end - start + 1));
}
