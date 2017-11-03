/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 14:05:25 by chaueur           #+#    #+#             */
/*   Updated: 2015/01/23 18:08:35 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_flags(const char **format)
{
	int		flags;

	flags = 0;
	while (**format)
	{
		if (**format == '#')
			flags |= ALTERNATE;
		else if (**format == '0')
			flags |= ZEROPAD;
		else if (**format == '+')
			flags |= PLUS;
		else if (**format == ' ')
			flags |= SPACE;
		else if (**format == '-')
			flags |= LEFT;
		else
			break ;
		(*format)++;
	}
	return (flags);
}

int			get_field_width(const char **format)
{
	int		field_width;

	field_width = 0;
	while (ft_isdigit(**format))
	{
		if (!field_width)
			field_width = ft_atoi(*format);
		(*format)++;
	}
	return (field_width);
}

int			get_precision(const char **format)
{
	int		precision;

	precision = -1;
	while (**format)
	{
		if (**format == '.')
		{
			precision = 0;
			(*format)++;
			precision = ft_atoi(*format);
			if (ft_isdigit(**format))
			{
				while (ft_isdigit(**format))
					(*format)++;
			}
			return (precision);
		}
		return (precision);
	}
	return (precision);
}

char		*get_len_modifier(const char **format)
{
	char	*len_modifier;
	char	*tmp;

	len_modifier = 0;
	if (**format && (tmp = ft_strchr(LEN_MOD, **format)))
	{
		len_modifier = ft_strnew(2);
		len_modifier[0] = **format;
		(*format)++;
		if (**format == 'h' || **format == 'l')
		{
			len_modifier[1] = **format;
			(*format)++;
		}
	}
	return (len_modifier);
}

char		get_converter(const char **format)
{
	char	converter;

	converter = 0;
	if (**format)
	{
		converter = **format;
		(*format)++;
		return (converter);
	}
	return (converter);
}
