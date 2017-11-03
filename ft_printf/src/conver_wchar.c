/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conver_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 17:56:00 by chaueur           #+#    #+#             */
/*   Updated: 2015/01/23 18:07:45 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*wstr_to_str(wchar_t *wstr, t_opt opt)
{
	char			*str;
	char			*trash;

	str = NULL;
	if (!wstr)
		return (NULL);
	if (!*wstr)
		return (ft_strdup("\0"));
	str = wint_to_str(*wstr++);
	while (*wstr)
	{
		trash = wint_to_str(*wstr);
		if (opt.precision >= 0)
		{
			if ((int)ft_strlen(trash) + (int)ft_strlen(str) <= opt.precision)
				str = ft_strjoin(str, trash);
		}
		else
			str = ft_strjoin(str, trash);
		free(trash);
		wstr++;
	}
	return (str);
}

char		*wint_to_str2(wint_t wint, char *str)
{
	if (wint < 0xFFFF)
	{
		if (!(str))
			str = ft_strnew(3);
		str[0] = (((wint & 0xF000) >> 12) + 0xE0);
		str[1] = (((wint & 0x0Fc0) >> 6) + 0x80);
		str[2] = ((wint & 0x003F) + 0x80);
	}
	else
	{
		if (!(str))
			str = ft_strnew(4);
		str[0] = (((wint & 0x1c0000) >> 18) + 0xF0);
		str[1] = (((wint & 0x03F000) >> 12) + 0x80);
		str[2] = (((wint & 0x0Fc0) >> 6) + 0x80);
		str[3] = ((wint & 0x003F) + 0x80);
	}
	return (str);
}

char		*wint_to_str(wint_t wint)
{
	char			*str;

	str = NULL;
	if (!wint)
		return (str);
	if (wint < 0x7F)
	{
		if (!str)
			str = ft_strnew(1);
		*str = wint;
	}
	else if (wint > 0x7F && wint < 0x10FFFF)
	{
		if (wint < 0x07FF)
		{
			if (!str)
				str = ft_strnew(2);
			str[0] = (((wint & 0x07c0) >> 6) + 0xc0);
			str[1] = ((wint & 0x003F) + 0x80);
		}
		else
			str = wint_to_str2(wint, str);
	}
	return (str);
}
