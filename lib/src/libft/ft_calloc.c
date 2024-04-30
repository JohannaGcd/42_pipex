/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 11:05:48 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/03 16:46:10 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	byte_size;
	void	*ptr;

	if (size != 0 && nmemb > INT_MAX / size)
		return (0);
	byte_size = nmemb * size;
	ptr = malloc(byte_size);
	if (!ptr)
		return (NULL);
	else
		ft_memset(ptr, 0, byte_size);
	return (ptr);
}
