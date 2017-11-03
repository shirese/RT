/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 09:40:15 by chaueur           #+#    #+#             */
/*   Updated: 2014/11/11 13:39:07 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i] != '\0' && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			i++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

char		**ft_strspliter(char **s_split, const char *s, char c, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			len++;
		}
		if (len != 0)
		{
			s_split[j++] = ft_strsub(s, i - len, len);
			len = 0;
		}
	}
	return (s_split);
}

char		**ft_strsplit(char const *s, char c)
{
	int				nb_word;
	size_t			len;
	char			**s_split;

	if (!s)
		return (NULL);
	nb_word = ft_count_words(s, c);
	len = 0;
	s_split = (char **)ft_memalloc(sizeof(char*) * (nb_word + 1));
	s_split = ft_strspliter(s_split, s, c, len);
	return (s_split);
}
