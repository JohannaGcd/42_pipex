/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit_unsigned.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:29:24 by jguacide          #+#    #+#             */
/*   Updated: 2023/11/14 14:38:02 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit_unsigned(unsigned long long ptr, unsigned int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (ptr < base)
		return (print_char(symbols[ptr]));
	else
	{
		count = print_digit_unsigned(ptr / base, base);
		return (count + print_digit_unsigned(ptr % base, base));
	}
}
