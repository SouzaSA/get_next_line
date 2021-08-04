/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-alva <sde-alva@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:36:56 by sde-alva          #+#    #+#             */
/*   Updated: 2021/08/03 22:39:49 by sde-alva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_buff(char **str_buff)
{
	size_t	i;
	size_t	line_len;
	char	*str;
	char	*tmp;

	i = 0;
	str = NULL;
	if (*str_buff && (*str_buff)[0] != '\0')
	{
		line_len = ft_strlen_set(*str_buff, "\n");
		str = (char *)malloc((line_len + 1) * sizeof(char));
		while (i < line_len)
		{
			str[i] = (*str_buff)[i];
			i++;
		}
		str[line_len] = '\0';
		tmp = *str_buff;
		*str_buff = ft_strjoin(*str_buff + line_len, "");
		free(tmp);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*to_read = NULL;
	char		*str;
	char		buff[BUFFER_SIZE + 1];
	size_t		gotten;

	str = NULL;
	if (fd >= 0)
	{
		gotten = read(fd, buff, BUFFER_SIZE);
		if (gotten > 0)
		{
			buff[gotten] = '\0';
			while (gotten > 0 && !ft_strchr(buff, '\n'))
			{
				str = to_read;
				to_read = ft_strjoin(to_read, buff);
				if (str)
					free(str);
				gotten = read(fd, buff, BUFFER_SIZE);
				buff[gotten] = '\0';
			}
			if (gotten > 0)
			{
				str = to_read;
				to_read = ft_strjoin(to_read, buff);
				if (str)
					free(str);
			}
		}
		if (to_read)
			str = ft_gnl_buff(&to_read);
	}
	if (!str && to_read)
		free(to_read);
	return (str);
}
