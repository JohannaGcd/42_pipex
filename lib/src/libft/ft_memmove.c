/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 11:38:48 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/03 17:02:03 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*new_dest;
	const unsigned char	*new_src;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	new_dest = (unsigned char *)dest;
	new_src = (unsigned char *)src;
	i = 0;
	if (new_dest < new_src)
	{
		while (i < n)
		{
			new_dest[i] = new_src[i];
			i++;
		}
	}
	else
		while (n--)
			new_dest[n] = new_src[n];
	return (dest);
}
