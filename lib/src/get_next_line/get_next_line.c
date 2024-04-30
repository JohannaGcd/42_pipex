/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/03 10:39:18 by jguacide      #+#    #+#                 */
/*   Updated: 2024/02/28 17:00:36 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_nextline(char *my_static_buffer)
{
	int		i;
	char	*next_line;

	i = 0;
	if (ft_strlen(my_static_buffer) == 0)
		return (ft_free(&my_static_buffer));
	while (my_static_buffer[i] != '\n' && my_static_buffer[i])
		i++;
	if (my_static_buffer[i] == '\n')
		i++;
	next_line = ft_strdup(&my_static_buffer[i]);
	ft_free(&my_static_buffer);
	if (!next_line)
		return (NULL);
	return (next_line);
}

// Extract the line from the content read (only before '\n')
char	*save_line(char *my_static_buffer)
{
	int		len;
	int		j;
	char	*line;

	len = 0;
	if (ft_strlen(my_static_buffer) == 0)
		return (NULL);
	while (my_static_buffer[len] != '\n' && my_static_buffer[len])
		len++;
	if (my_static_buffer[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (my_static_buffer[j] && my_static_buffer[j] != '\n')
	{
		line[j] = my_static_buffer[j];
		j++;
	}
	if (my_static_buffer[j] == '\n')
		line[j++] = '\n';
	line[j++] = '\0';
	return (line);
}

// Read from file until '\n' and join them in myStaticBuffer
char	*read_from_file(int fd, char *my_static_buffer)
{
	ssize_t	bytesread;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&my_static_buffer));
	buffer[0] = '\0';
	bytesread = 1;
	while (!ft_strchr(my_static_buffer, '\n') && bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
		{
			ft_free(&buffer);
			return (ft_free(&my_static_buffer));
		}
		buffer[bytesread] = '\0';
		my_static_buffer = ft_strjoin_gnl(my_static_buffer, buffer);
		if (!my_static_buffer)
			return (ft_free(&buffer));
	}
	ft_free(&buffer);
	return (my_static_buffer);
}

// Combine the helper functions together
char	*get_next_line(int fd)
{
	static char	*my_static_buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	my_static_buffer = read_from_file(fd, my_static_buffer);
	if (!my_static_buffer)
		return (NULL);
	line = save_line(my_static_buffer);
	if (!line)
		return (ft_free(&my_static_buffer));
	my_static_buffer = save_nextline(my_static_buffer);
	if (!my_static_buffer)
		return (ft_free(&line));
	return (line);
}
/*
int	main(void)
{
	int		file;
	char	*line;

	// file = open(argv[1], O_RDONLY);
	file = open("test.txt", O_RDONLY);
	if (file < 0)
	{
		write(1, "error", 5);
		return (-1);
	}
	line = get_next_line(file);
	while (line != NULL)
	{
		printf("%s$", line);
		ft_free(&line);
		line = get_next_line(file);
	}
	close(file);
	return (0);
}*/
