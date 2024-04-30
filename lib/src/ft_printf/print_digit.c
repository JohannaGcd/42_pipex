/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:59:12 by jguacide          #+#    #+#             */
/*   Updated: 2023/11/14 14:35:57 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit(long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (1 + print_digit(-n, base));
	}
	else if (n < base)
	{
		return (print_char(symbols[n]));
	}
	else
	{
		count = print_digit(n / base, base);
		return (count + print_digit(n % base, base));
	}
}
