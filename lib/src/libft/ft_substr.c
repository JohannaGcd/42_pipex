/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 16:05:40 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/01 11:53:52 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int				i;
	char			*sub;
	unsigned int	len_s;

	len_s = ft_strlen(s);
	i = 0;
	if (start >= len_s || len == 0)
		return (ft_strdup(""));
	if (len >= len_s - start)
		len = len_s - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	else
	{
		while (s[i] && len > 0)
		{
			sub[i] = s[start];
			i++;
			start++;
			len--;
		}
	}
	sub[i] = '\0';
	return (sub);
}

/*
int main(void)
{
	char const s[] = "hola";
	unsigned int start = 0;
	size_t len = 18446744073709551615;
	
	printf("%s\n", ft_substr(s, start, len));
	
	return (0);
}
*/
