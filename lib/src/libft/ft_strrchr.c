/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 11:43:26 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/03 16:58:56 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	copy_c;

	copy_c = (unsigned char)c;
	i = 0;
	while (s[i])
		i++;
	if (copy_c == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == copy_c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
