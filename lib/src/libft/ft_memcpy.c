/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 11:37:46 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/03 16:45:40 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*b;
	const unsigned char	*c;
	size_t				i;

	b = (unsigned char *)dest;
	c = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		b[i] = c[i];
		i++;
	}
	return (dest);
}
