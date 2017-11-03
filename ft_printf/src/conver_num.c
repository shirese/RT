/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conver_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 17:59:25 by chaueur           #+#    #+#             */
/*   Updated: 2015/01/23 18:06:03 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		apply_alternate_format(t_opt *opt, char *arg, int *len)
{
	if ((*opt).flags & HEXOCT)
	{
		if (*arg == '0' && !((*opt).conv == 'p') && ((*opt).precision != 0))
			return ;
		else if ((*opt).conv == 'x' || (*opt).conv == 'p')
		{
			if ((*opt).conv == 'x' && *arg == '0')
				return ;
			ft_putstr("0x");
			(*len) += 2;
		}
		else if ((*opt).conv == 'X')
		{
			ft_putstr("0X");
			(*len) += 2;
		}
		else if ((*opt).conv == 'o' || (*opt).conv == 'O')
		{
			ft_putchar('0');
			(*len)++;
		}
	}
}

void		len_mod_hexoct(va_list args, t_opt opt, char **arg, int base)
{
	if (!ft_strcmp("hh", opt.len_modifier))
		*arg = ft_itoa_unsig_base((unsigned char)va_arg(args, int), base);
	else if (!ft_strcmp("h", opt.len_modifier))
		*arg = ft_itoa_unsig_base((unsigned short)va_arg(args, int), base);
	else if (!ft_strcmp("l", opt.len_modifier))
		*arg = ft_itoa_unsig_base(va_arg(args, unsigned long), base);
	else if (!ft_strcmp("ll", opt.len_modifier))
		*arg = ft_itoa_unsig_base(va_arg(args, unsigned long long), base);
	else if (!ft_strcmp("j", opt.len_modifier))
		*arg = ft_itoa_unsig_base(va_arg(args, uintmax_t), base);
	else if (!ft_strcmp("z", opt.len_modifier))
		*arg = ft_itoa_unsig_base(va_arg(args, size_t), base);
}

void		len_mod_number(va_list args, t_opt opt, char **arg, int base)
{
	if (opt.conv == 'c' || opt.conv == 'C')
		*arg = wint_to_str(va_arg(args, wint_t));
	else if (opt.conv == 's' || opt.conv == 'S')
		*arg = wstr_to_str(va_arg(args, wchar_t *), opt);
	else if (!ft_strcmp("hh", opt.len_modifier))
		*arg = ft_itoa_base((signed char)va_arg(args, int), base);
	else if (!ft_strcmp("h", opt.len_modifier))
		*arg = ft_itoa_base((short)va_arg(args, int), base);
	else if (!ft_strcmp("j", opt.len_modifier))
		*arg = ft_itoa_base(va_arg(args, intmax_t), base);
	else if (!ft_strcmp("z", opt.len_modifier))
		*arg = ft_itoa_base(va_arg(args, size_t), base);
	else if (!ft_strcmp("ll", opt.len_modifier))
		*arg = ft_itoa_base(va_arg(args, long long), base);
	else if (!ft_strcmp("l", opt.len_modifier))
		*arg = ft_itoa_base(va_arg(args, long), base);
}

void		len_mod_long(va_list args, t_opt opt, char **arg, int base)
{
	if (opt.conv == 'O' || opt.conv == 'U')
	{
		if (!ft_strcmp("l", opt.len_modifier))
			*arg = ft_itoa_unsig_base(va_arg(args, long), base);
		else if (!ft_strcmp("ll", opt.len_modifier))
			*arg = ft_itoa_unsig_base(va_arg(args, long long), base);
		else if (!ft_strcmp("j", opt.len_modifier))
			*arg = ft_itoa_unsig_base(va_arg(args, uintmax_t), base);
		else if (!ft_strcmp("z", opt.len_modifier))
			*arg = ft_itoa_unsig_base(va_arg(args, size_t), base);
		else
			*arg = ft_itoa_unsig_base((unsigned short)va_arg(args, long), base);
	}
	else
	{
		if (!ft_strcmp("j", opt.len_modifier))
			*arg = ft_itoa_base(va_arg(args, intmax_t), base);
		else if (!ft_strcmp("z", opt.len_modifier))
			*arg = ft_itoa_base(va_arg(args, size_t), base);
		else if (!ft_strcmp("ll", opt.len_modifier))
			*arg = ft_itoa_base(va_arg(args, long long), base);
		else
			*arg = ft_itoa_base(va_arg(args, long), base);
	}
}

void		apply_len_mod(va_list args, t_opt opt, char **arg)
{
	int		base;

	base = 10;
	if (opt.conv == 'o' || opt.conv == 'O')
		base = 8;
	else if (opt.conv == 'x' || opt.conv == 'X' || opt.conv == 'p')
		base = 16;
	if (ft_strchr(LONG, opt.conv))
		len_mod_long(args, opt, arg, base);
	else if (opt.flags & HEXOCT || opt.conv == 'u')
		len_mod_hexoct(args, opt, arg, base);
	else
		len_mod_number(args, opt, arg, base);
}
