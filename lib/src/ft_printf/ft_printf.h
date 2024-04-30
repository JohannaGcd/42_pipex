/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 10:19:53 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/15 10:57:45 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

int		print_char(int c);
int		print_string(char *s);
int		print_digit(long n, int base);
int		print_format(char specifier, va_list ap);
int		ft_printf(const char *format, ...);
int		print_address(unsigned long long ptr);
int		print_digit(long n, int base);
int		print_digit_bighex(long n, int base);
int		print_digit_unsigned(unsigned long long ptr, unsigned int base);

#endif
