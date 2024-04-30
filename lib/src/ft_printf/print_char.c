/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 14:55:47 by jguacide      #+#    #+#                 */
/*   Updated: 2023/11/15 17:29:50 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int c)
{
	if (c == '%')
		return (write(1, "%", 1));
	else
		return (write(1, &c, 1));
}
