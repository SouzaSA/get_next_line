/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-alva <sde-alva@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 10:21:23 by sde-alva          #+#    #+#             */
/*   Updated: 2021/08/04 20:50:11 by sde-alva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*match;
	int		i;

	i = 0;
	match = NULL;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (s[i] == (char) c)
			{
				match = (char *)s + i;
				break ;
			}
			i++;
		}
		if (c == '\0')
			match = (char *)s + i;
	}
	return (match);
}

char	*ft_strjoin_mod(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*dst;

	i = 0;
	s1_len = ft_strlen_set(s1, "\0");
	s2_len = ft_strlen_set(s2, "\0");
	dst = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (dst)
	{
		while (s1[i] != '\0' || s2[i] != '\0')
		{
			if (i < s1_len)
				dst[i] = s1[i];
			if (i < s2_len)
				dst[i + s1_len] = s2[i];
			i++;
		}
		dst[s1_len + s2_len] = '\0';
	}
	return (dst);
}

size_t	ft_strlen_set(const char *s, const char *set)
{
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	if (s)
	{
		found = 0;
		while (s[i] != '\0' && !found)
		{
			j = 0;
			while (set[j] != '\0')
			{
				if (s[i] == set[j])
					found = 1;
				j++;
			}
			i++;
		}
		if (s[i] == '\n' && s[i - 1] != '\n')
			i++;
	}
	return (i);
}
