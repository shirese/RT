/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conver_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 17:38:47 by chaueur           #+#    #+#             */
/*   Updated: 2015/01/23 18:46:44 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void		apply_space(t_opt *opt, int *len)
{
	if (!((*opt).flags & SIGN) && ft_strchr(SIGNED, (*opt).conv))
	{
		(*len)++;
		(*opt).field_width--;
		ft_putchar(' ');
	}
}

void		apply_precision(char **arg, t_opt *opt, int *len)
{
	int		prec_len;

	prec_len = 0;
	if ((*opt).conv == 's' || (*opt).conv == 'S')
	{
		if ((*opt).precision < (int)ft_strlen(*arg))
			*arg = ft_strsub(*arg, 0, (*opt).precision);
	}
	else
	{
		if ((*opt).precision > (int)ft_strlen(*arg))
		{
			prec_len = ((*opt).precision) - ft_strlen(*arg);
			if ((*opt).conv == 'o' || (*opt).conv == 'O')
				(*opt).flags & ALTERNATE ? prec_len-- : 0;
			*len += prec_len;
		}
		while (prec_len-- > 0)
			ft_putchar('0');
		(*opt).precision -= ft_strlen(*arg);
	}
}

void		apply_field_width(char **arg, t_opt *opt, int *len)
{
	unsigned char	c;

	c = ((*opt).flags & ZEROPAD) ? '0' : ' ';
	if ((*opt).flags & ALTERNATE && ((*opt).field_width -= 2))
		((*opt).conv == 'o' || (*opt).conv == 'O') ? (*opt).field_width++ : 0;
	if (arg && *arg)
	{
		if ((*opt).precision > 0 && ft_strchr(NUMBER, (*opt).conv))
		{
			if ((*opt).precision < (*opt).field_width)
				(*opt).field_width -= (*opt).precision;
			else
				(*opt).field_width = 0;
		}
		else if ((*opt).field_width > (int)ft_strlen(*arg))
			(*opt).field_width -= ft_strlen(*arg);
		else
			(*opt).field_width = 0;
	}
	((*opt).conv == 'c' && !*arg) ? (*opt).field_width-- : 0;
	*len += (*opt).field_width;
	while ((*opt).field_width--)
		ft_putchar(c);
}

char		*simple_char(unsigned int c)
{
	char			*str;

	str = NULL;
	if (c)
	{
		str = ft_strnew(1);
		*str = c;
	}
	return (str);
}

void		check_arg(t_opt *opt, char *arg)
{
	if (ft_strchr(NUMBER, (*opt).conv) && (*arg == '-'))
		(*opt).flags |= SIGN;
	if ((*opt).flags & ZEROPAD || (*opt).precision >= 0)
	{
		if ((*opt).flags & SIGN)
		{
			ft_putchar('-');
			((*opt).precision >= 0) ? (*opt).precision++ : 0;
		}
		if ((*opt).flags & PLUS)
		{
			ft_putchar('+');
			(*opt).field_width--;
		}
	}
}
