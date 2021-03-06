/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:01:15 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/27 16:07:19 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char *tmp_s;

	if (n)
	{
		tmp_s = s;
		while (n)
		{
			*tmp_s = 0;
			n--;
			tmp_s++;
		}
	}
}
