/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:21:45 by jguacide          #+#    #+#             */
/*   Updated: 2023/10/19 16:39:38 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*strmapi;

	len = ft_strlen(s);
	if (!s)
		return (NULL);
	strmapi = malloc(sizeof(char) * (len + 1));
	if (!strmapi)
		return (NULL);
	i = 0;
	while (s[i])
	{
		strmapi[i] = f(i, s[i]);
		i++;
	}
	strmapi[i] = '\0';
	return (strmapi);
}
