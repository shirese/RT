/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:03:29 by chaueur           #+#    #+#             */
/*   Updated: 2017/06/23 11:36:25 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*ft_strcpy(char *dst, const char *src)
{
	size_t			i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char				*ft_strcat(char *s1, const char *s2)
{
	char			*tmp;

	tmp = s1;
	while (*s1)
		s1++;
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return (tmp);
}

char				*ft_strmerge_buff(char *s, char const *buff)
{
	char			*new;

	new = (char*)malloc((ft_strlen(s) + ft_strlen(buff) + 1) * sizeof(char));
	if (new)
	{
		ft_strcpy(new, s);
		ft_strcat(new, buff);
		free(s);
	}
	return (new);
}

int					get_next_line(int const fd, char **line)
{
	static char		buffer[257][BUFF_SIZE + 1] = {{'\0'}};
	int				ret;
	char			*tmp;

	ret = 1;
	if (*line)
		free(*line);
	*line = ft_strdup(buffer[fd]);
	while (*line && !(tmp = ft_strchr(*line, '\n')) \
		&& fd >= 0 && (ret = read(fd, buffer[fd], BUFF_SIZE)) > 0)
	{
		buffer[fd][ret] = '\0';
		*line = ft_strmerge_buff(*line, buffer[fd]);
	}
	if (tmp && (*line) && fd >= 0)
	{
		ft_strcpy(buffer[fd], tmp + 1);
		*tmp = '\0';
	}
	else if (ret <= 0)
		buffer[fd][0] = '\0';
	if (!(*line) || fd < 0)
		ret = (-1);
	return ((ret > 0) ? 1 : ret);
}
