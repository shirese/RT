/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 18:57:44 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/10 19:19:53 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (size == SIZE_MAX)
		return (0);
	str = ft_memalloc(size + 1);
	if (str)
	{
		ft_strclr(str);
		return (str);
	}
	else
		return (NULL);
}
