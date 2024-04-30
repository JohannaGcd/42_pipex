/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit_bighex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:29:25 by jguacide          #+#    #+#             */
/*   Updated: 2023/11/14 16:04:22 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit_bighex(long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789ABCDEF";
	if (n < 0)
	{
		write(1, "-", 1);
		return (1 + print_digit_bighex(-n, 16));
	}
	else if (n < base)
		return (print_char(symbols[n]));
	else
	{
		count = print_digit_bighex(n / base, base);
		return (count + print_digit_bighex(n % base, base));
	}
}
