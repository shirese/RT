/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:42:32 by chaueur           #+#    #+#             */
/*   Updated: 2016/12/16 14:28:26 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*s_sub;
	char	*s_start;
	char	*s_sub_end;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if ((start + len) > s_len)
		return (NULL);
	s_sub = ft_strnew(s_len);
	if (!s_sub)
		return (NULL);
	s_start = (char *)(s + start);
	s_sub_end = s_sub;
	while (len--)
		*s_sub_end++ = *s_start++;
	s_sub_end = 0;
	return (s_sub);
}
