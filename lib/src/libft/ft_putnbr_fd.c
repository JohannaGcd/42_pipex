/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:33:11 by jguacide      #+#    #+#                 */
/*   Updated: 2023/10/24 16:33:47 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_string(long n, int fd)
{
	char	c;

	if (n / 10 == 0)
	{
		c = n % 10 + '0';
		write(fd, &c, 1);
		return ;
	}
	fill_string(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;

	long_n = (long)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		long_n *= -1;
	}
	fill_string(long_n, fd);
}
