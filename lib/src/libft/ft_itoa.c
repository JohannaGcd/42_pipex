/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:51:12 by jguacide          #+#    #+#             */
/*   Updated: 2023/10/24 18:07:05 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_string(char *result, long n, size_t strl)
{
	if (n / 10 == 0)
	{
		result[strl - 1] = n % 10 + '0';
		return ;
	}
	fill_string(result, n / 10, strl - 1);
	result[strl - 1] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	size_t	strl;
	char	*result;
	int		temp;

	temp = n;
	strl = 1;
	while (temp / 10 != 0)
	{
		temp /= 10;
		strl++;
	}
	if (n < 0)
		strl++;
	result = malloc((strl + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		fill_string((result + 1), (long)n * (-1), strl - 1);
	}
	else
		fill_string(result, n, strl);
	result[strl] = '\0';
	return (result);
}
