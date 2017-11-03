/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:39:32 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/17 16:41:30 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_ftoa(double n)
{
	int				one;
	int				state;
	char			*ptr;
	char			*ret;
	double			two;

	state = (n < 0) ? 1 : 0;
	ret = ft_itoa(n);
	ptr = ft_strdup(".");
	ret = ft_strfjoin(&ret, &ptr, 3);
	n *= state ? -1 : 1;
	one = (int)n;
	two = n - one;
	while (++state && (size_t)state < (sizeof(n) - 1))
		two *= 10;
	ptr = ft_itoa((int)two);
	ret = ft_strfjoin(&ret, &ptr, 3);
	return (ret);
}
