/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 12:13:49 by chaueur           #+#    #+#             */
/*   Updated: 2015/01/23 19:35:56 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_non_format(const char **format, t_opt *opt, int *len)
{
	if ((*opt).field_width)
		apply_field_width(NULL, opt, len);
	ft_putchar(**format);
	(*len)++;
	(*format)++;
}

void		get_options(const char **format, va_list args, int *len, t_opt *opt)
{
	(*opt).flags = get_flags(format);
	(*opt).field_width = get_field_width(format);
	(*opt).precision = get_precision(format);
	(*opt).len_modifier = get_len_modifier(format);
	(*opt).conv = get_converter(format);
	if ((*opt).conv == 'o' || (*opt).conv == 'O'
		|| (*opt).conv == 'x' || (*opt).conv == 'X' || (*opt).conv == 'p')
	{
		(*opt).flags |= HEXOCT;
		if ((*opt).conv == 'p')
			(*opt).flags |= ALTERNATE;
	}
	if ((*opt).conv)
		convert_args(args, opt, len);
	else if (**format == '%')
	{
		ft_putchar(**format);
		(*format)++;
		(*len)++;
	}
	ft_memset(&opt, 0, sizeof(*opt));
}

int			print(const char *format, va_list args)
{
	t_opt	opt;
	int		len;

	ft_memset(&opt, 0, sizeof(opt));
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				return (len);
			if (*format == '%')
			{
				ft_putchar(*format);
				format++;
				len++;
			}
			else
				get_options(&format, args, &len, &opt);
		}
		else
			print_non_format(&format, &opt, &len);
	}
	return (len);
}

int			ft_printf(const char *format, ...)
{
	va_list		args;
	char		*i;

	if (format)
	{
		va_start(args, format);
		i = setlocale(LC_ALL, "");
		if (i)
			return (print(format, args));
		else
			ft_putstr("Locale not set\n");
	}
	return (-1);
}
