/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:40:42 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/17 16:42:33 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strfjoin(char **s1, char **s2, int pfree)
{
	char			*ret;

	ret = ft_strjoin((const char *)*s1, (const char *)*s2);
	if (pfree == 1 || pfree == 3)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (pfree == 2 || pfree == 3)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (ret);
}

char				*ft_strfjoin1(char **s1, char *s2, int pfree)
{
	pfree = pfree ? 1 : 0;
	return (ft_strfjoin(s1, &s2, pfree));
}

char				*ft_strfjoin2(char *s1, char **s2, int pfree)
{
	pfree = pfree ? 2 : 0;
	return (ft_strfjoin(&s1, s2, pfree));
}
