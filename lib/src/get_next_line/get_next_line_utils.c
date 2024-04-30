/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:39:37 by jguacide          #+#    #+#             */
/*   Updated: 2024/04/02 18:15:27 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **s)
{
	if (*s)
		free(*s);
	*s = NULL;
	return (NULL);
}

/*char	*ft_strdup(char const *s)
{
	size_t	len;
	size_t	i;
	char	*s_copy;

	i = 0;
	len = ft_strlen(s);
	s_copy = malloc(len + 1);
	if (!s_copy)
		return (NULL);
	while (s[i])
	{
		s_copy[i] = s[i];
		i++;
	}
	s_copy[i] = '\0';
	return (s_copy);
}

size_t	ft_strlen(char const *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char const *s, int c)
{
	char	copy_c;
	int		i;

	copy_c = (char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == copy_c)
			return ((char *)&s[i]);
		i++;
	}
	if (copy_c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}*/

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new_string;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	new_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_string || !s1 || !s2)
		return (ft_free(&s1));
	i = -1;
	while (s1[++i] != 0)
		new_string[i] = s1[i];
	j = -1;
	while (s2[++j] != 0)
		new_string[i + j] = s2[j];
	new_string[i + j] = '\0';
	ft_free(&s1);
	return (new_string);
}
