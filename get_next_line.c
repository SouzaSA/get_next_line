/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-alva <sde-alva@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:36:56 by sde-alva          #+#    #+#             */
/*   Updated: 2021/08/10 16:46:39 by sde-alva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*to_read = NULL;
	char		*str;

	str = NULL;
	if (BUFFER_SIZE > 0 && fd >= 0 && read(fd, str, 0) == 0)
	{
		ft_push_line(fd, &to_read);
		if (to_read)
			str = ft_pop_line(&to_read);
	}
	if (!str)
		free(to_read);
	return (str);
}
