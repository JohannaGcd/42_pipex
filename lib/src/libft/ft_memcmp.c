/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 11:46:18 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/03 16:48:22 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*alias_s1;
	const unsigned char	*alias_s2;

	i = 0;
	alias_s1 = (unsigned char *)s1;
	alias_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if ((alias_s1[i] != alias_s2[i]))
			return (alias_s1[i] - alias_s2[i]);
		i++;
	}
	return (0);
}
