/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:36:18 by jguacide          #+#    #+#             */
/*   Updated: 2024/06/12 13:16:19 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

char	*free_double(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	wait_for_children(pid_t id1, pid_t id2, int fd[])
{
	int	status1;
	int	status2;

	close(fd[0]);
	waitpid(id1, &status1, 0);
	if (WIFSIGNALED(status1))
		perror("SIGINTERUPT");
	waitpid(id2, &status2, 0);
	return (check_status(status2));
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (127);
}

char	*check_direct_paths(char *cmd)
{
	if (cmd[0] == '/'
		|| cmd[0] == '.'
		|| cmd[0] == '~')
		return (ft_strdup(cmd));
	return (NULL);
}

char	*format_bin_path(char *path_dir, char *cmd)
{
	char	*formatted_path;
	char	*step1_path;

	step1_path = ft_strjoin(path_dir, "/");
	if (!step1_path)
		return (NULL);
	formatted_path = ft_strjoin(step1_path, &cmd[0]);
	if (!formatted_path)
		return (free(step1_path), NULL);
	return (free(step1_path), formatted_path);
}
