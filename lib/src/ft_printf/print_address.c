/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:17:28 by jguacide          #+#    #+#             */
/*   Updated: 2023/11/14 15:14:01 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_address(unsigned long long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		return (count += 5);
	}
	else
	{
		count += write(1, "0x", 2);
		count += print_digit_unsigned(ptr, 16);
	}
	return (count);
}
