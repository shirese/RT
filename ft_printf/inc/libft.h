/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:52:55 by chaueur           #+#    #+#             */
/*   Updated: 2017/12/04 17:37:06 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <wchar.h>

# define INT_DIGITS 19
# define INT_UNS_DIGITS 21

typedef struct s_coord	t_coord;
struct	s_coord
{
	int			x;
	int			xx;
	int			y;
	int			yy;
	int			z;
	t_coord		*next;
};
typedef struct s_list	t_list;
struct	s_list
{
	t_coord		*coord;
	size_t		coord_size;
	t_list		*next;
};

t_list	*ft_lstnew(t_coord *list, size_t coord_size);
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void	ft_putchar(char c);
void	ft_putwchar(wint_t c);
void	ft_putendl(char const *s);
void	ft_putstr(char const *s);
void	ft_putwstr(wchar_t *s);
void	ft_putnbr(int n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	*ft_strcat(char *s1, const char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strncat(char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *s1, const char *s2);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
float	ft_atof(char *str);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isblank(char c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isalnum(int c);
int		ft_toupper(int c);
char	*ft_strtoupper(char *s);
int		ft_tolower(int c);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char(*)));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strrev(char *s);
char	*ft_strnrev(char *s, int n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strfjoin(char **s1, char **s2, int pfree);
char	*ft_strtrim(char const *s);
char	**ft_strsplit(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_itoa_base(long long n, int base);
char	*ft_itoa_unsig_base(long long unsigned n, int base);
char	*ft_ftoa(double n, size_t precision);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putnbr_lbase(unsigned long n, char *base);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
#endif
