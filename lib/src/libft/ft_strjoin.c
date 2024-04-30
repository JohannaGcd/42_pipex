/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:36:32 by jguacide          #+#    #+#             */
/*   Updated: 2023/10/23 16:36:14 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	int		i;
	int		j;

	new_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_string[i] = s2[j];
		j++;
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
