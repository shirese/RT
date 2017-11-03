/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtopupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 16:53:19 by chaueur           #+#    #+#             */
/*   Updated: 2014/12/15 17:11:09 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtoupper(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		*tmp = ft_toupper(*tmp);
		tmp++;
	}
	return (s);
}
