/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conver_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 18:27:50 by chaueur           #+#    #+#             */
/*   Updated: 2018/01/08 10:43:16 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		apply_flags(t_opt *opt, char **arg, int *len)
{
	if (opt->flags & LEFT || opt->precision > 0)
		opt->flags &= ~ZEROPAD;
	(*arg) ? check_arg(opt, *arg) : 0;
	if (opt->flags & ALTERNATE && opt->flags & ZEROPAD)
		apply_alternate_format(opt, *arg, len);
	if (opt->flags & SPACE && !(opt->flags & PLUS))
		apply_space(opt, len);
	if (opt->field_width && !(opt->flags & LEFT))
		apply_field_width(arg, opt, len);
	if (opt->flags & ALTERNATE && !(opt->flags & ZEROPAD))
		apply_alternate_format(opt, *arg, len);
	if (*arg && ft_strcmp(*arg, "(null)"))
	{
		if (opt->flags & PLUS && !(opt->flags & SIGN)
			&& !(ft_strchr(UNSIG, opt->conv)))
		{
			(*len)++;
			(opt->flags & ZEROPAD) ? 0 : ft_putchar('+');
		}
		if (opt->precision > 0 && (!(opt->conv == 'c')
					&& !(opt->conv == 'C')))
			apply_precision(arg, opt, len);
	}
}

void		convert_nolenmod_args_2(va_list args, t_opt opt, char **arg)
{
	if (opt.conv == 's')
		*arg = va_arg(args, char *);
	else if (opt.conv == 'S')
		*arg = wstr_to_str(va_arg(args, wchar_t *), opt);
	else if (opt.conv == 'c')
		*arg = simple_char(va_arg(args, unsigned int));
	else if (opt.conv == 'p')
		*arg = ft_itoa_base(va_arg(args, unsigned long), 16);
	else if (opt.conv == 'D')
		*arg = ft_itoa_base(va_arg(args, long), 10);
	else if (opt.conv == 'U')
		*arg = ft_itoa_unsig_base(va_arg(args, unsigned long), 10);
	else if (opt.conv == 'C')
		*arg = wint_to_str(va_arg(args, wint_t));
}

void		convert_nolenmod_args(va_list args, t_opt opt, char **arg)
{
	*arg = NULL;
	if (opt.conv == 'd' || opt.conv == 'i')
		*arg = ft_itoa_base(va_arg(args, int), 10);
	if (opt.conv == 'f')
		*arg = ft_ftoa(va_arg(args, double), (opt.precision != -1) ? \
			opt.precision : 6);
	if (opt.conv == 'b')
		*arg = ft_itoa_base(va_arg(args, int), 2);
	else if (opt.conv == 'u')
		*arg = ft_itoa_unsig_base(va_arg(args, unsigned int), 10);
	else if (opt.conv == 'o')
		*arg = ft_itoa_unsig_base(va_arg(args, unsigned int), 8);
	else if (opt.conv == 'O')
		*arg = ft_itoa_unsig_base(va_arg(args, unsigned long), 8);
	else if (opt.conv == 'x')
		*arg = ft_itoa_unsig_base(va_arg(args, unsigned int), 16);
	else if (opt.conv == 'X')
		*arg = ft_itoa_unsig_base(va_arg(args, unsigned long), 16);
	else
		convert_nolenmod_args_2(args, opt, arg);
}

void		convert_args_2(t_opt *opt, int *len, char *arg)
{
	if (arg && ft_strcmp(arg, "(null)"))
		(*len) += ft_strlen(arg);
	if (!arg && ((opt->conv == 'c') || (opt->conv) == 'C'))
	{
		ft_putchar('\0');
		(*len)++;
	}
	else if (!(ft_strchr(CONVERTER, opt->conv)))
	{
		(*len)++;
		ft_putchar(opt->conv);
	}
	if (arg)
	{
		opt->conv == 'X' ? ft_strtoupper(arg) : 0;
		if ((opt->flags & SIGN) &&
				(opt->flags & ZEROPAD || opt->precision >= 0))
			ft_putstr(++arg);
		else
			ft_putstr(arg);
	}
	if (opt->flags & LEFT)
		apply_field_width(&arg, opt, len);
}

void		convert_args(va_list args, t_opt *opt, int *len)
{
	char		*arg;

	arg = NULL;
	if (!(ft_strchr(CONVERTER, opt->conv)))
		opt->field_width ? opt->field_width-- : 0;
	if (!opt->len_modifier)
		convert_nolenmod_args(args, *opt, &arg);
	else
		apply_len_mod(args, *opt, &arg);
	if ((!arg || !(ft_strcmp(arg, "(null)"))) &&
			((opt->conv == 's') || opt->conv == 'S'))
	{
		opt->flags &= ~PLUS;
		opt->field_width ? 0 : (arg = ft_strdup("(null)"));
		arg ? (*len) += ft_strlen(arg) : 0;
	}
	opt->conv == 'S' && opt->precision == 0 ? (arg = NULL) : 0;
	apply_flags(opt, &arg, len);
	if ((ft_strchr(NUMBER, opt->conv)) && *arg == '0' && !opt->precision)
		arg = NULL;
	convert_args_2(opt, len, arg);
	if (arg && opt->conv != 's')
		free(arg);
	ft_memset(opt, 0, sizeof(*opt));
}
