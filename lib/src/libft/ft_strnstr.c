/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 11:46:33 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/03 17:14:04 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while ((big[i + j] == little[j]) && (i + j) < len && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
