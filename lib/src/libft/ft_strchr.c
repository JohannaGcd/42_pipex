/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 11:42:24 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/15 15:03:11 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
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
}
