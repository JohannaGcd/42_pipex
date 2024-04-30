/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 17:54:15 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/15 17:35:43 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += print_string(va_arg(ap, char *));
	else if (specifier == 'd')
		count += print_digit((long)va_arg(ap, int), 10);
	else if (specifier == 'x')
		count += print_digit((long)va_arg(ap, unsigned int), 16);
	else if (specifier == 'X')
		count += print_digit_bighex((long)va_arg(ap, unsigned int), 16);
	else if (specifier == 'i')
		count += print_digit((int)va_arg(ap, int), 10);
	else if (specifier == 'u')
		count += print_digit((unsigned int)va_arg(ap, unsigned int), 10);
	else if (specifier == 'p')
		count += print_address(va_arg(ap, unsigned long long));
	else
		count += write(1, &specifier, 1);
	return (count);
}

int	check_edgecases(const char *f)
{
	int	count;

	count = 0;
	if (*(f + 1) == '\0')
		write(1, "-1", 2);
	else
		count += write(1, f, 1);
	return (count);
}

int	ft_printf(const char *f, ...)
{
	va_list	ap;
	int		count;

	if (!f)
		return (-1);
	count = 0;
	va_start(ap, f);
	while (*f)
	{
		if (*f == '%')
		{
			if ((*(f + 1) == '\0') || (!ft_strchr("csdxXiup%", *(f + 1))))
				count += check_edgecases(f);
			else
			{
				count += print_format(*(f + 1), ap);
				f++;
			}
		}
		else
			count += write(1, f, 1);
		++f;
	}
	va_end(ap);
	return (count);
}
