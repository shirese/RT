/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:33:56 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/09 15:35:48 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int equal;

	if (!s1 || !s2)
		return (0);
	equal = (ft_strcmp(s1, s2) == 0 ? 1 : 0);
	return (equal);
}
