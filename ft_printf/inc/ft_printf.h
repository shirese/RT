/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/12 11:50:28 by chaueur           #+#    #+#             */
/*   Updated: 2017/10/17 16:32:57 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <limits.h>
# include <locale.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <wchar.h>
# define HEXOCT		64
# define ALTERNATE	32
# define ZEROPAD	1
# define SIGN		2
# define PLUS		4
# define SPACE		8
# define LEFT		16
# define LONG "DOU"
# define CONVERTER "sSpdDfioOuUxXcC"
# define NUMBER "dfiuoOupxX"
# define UNSIG "oOpuxX"
# define SIGNED "di"
# define LEN_MOD "hljz"

typedef struct s_opt	t_opt;
struct		s_opt
{
	int			flags;
	int			field_width;
	int			precision;
	char		*len_modifier;
	char		conv;
};

int			get_flags(const char **format);
int			get_field_width(const char **format);
int			get_precision(const char **format);
char		*get_len_modifier(const char **format);
char		get_converter(const char **format);
void		convert_args(va_list args, t_opt *opt, int *len);
void		convert_nolenmod_args(va_list args, t_opt opt, char **arg);
void		convert_nolenmod_args_2(va_list args, t_opt opt, char **arg);
void		apply_len_mod(va_list args, t_opt opt, char **arg);
void		len_mod_number(va_list args, t_opt opt, char **arg, int base);
void		len_mod_hexoct(va_list args, t_opt opt, char **arg, int base);
void		check_arg(t_opt *opt, char *arg);
char		*convert_num(float num, t_opt *opt);
char		*wint_to_str(wint_t wint);
char		*wint_to_str2(wint_t wint, char *str);
char		*wstr_to_str(wchar_t *wstr, t_opt opt);
char		*simple_char(unsigned int c);
void		apply_field_width(char **arg, t_opt *opt, int *len);
void		apply_precision(char **arg, t_opt *opt, int *len);
void		apply_space(t_opt *opt, int *len);
void		apply_alternate_format(t_opt *opt, char *arg, int *len);

void		ft_putchar(char c);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcat(char *s1, const char *s2);
void		ft_strdel(char **as);
void		ft_putnbr(int n);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memalloc(size_t size);
void		ft_putchar(char c);
void		ft_putstr(char const *s);
void		ft_putnbr(int n);
char		*ft_itoa(int n);
char		*ft_ltoa(long n);
char		*ft_lltoa(long long n);
char		*ft_uitoa(unsigned int n);
char		*ft_ultoa(unsigned long n);
char		*ft_ulltoa(unsigned long long n);

int			ft_printf(const char *format, ...);
void		*ft_realloc(void *ptr, size_t new_size, size_t old_size);

#endif
