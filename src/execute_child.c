/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:36:05 by jguacide          #+#    #+#             */
/*   Updated: 2024/06/10 19:29:12 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <unistd.h>

// METHOD:
// This function executes the child process specified.
// Step 1: retrieves the command given, using argv
// Step 2: set_in_and_out opens the files specified & redirects the fd
// Step 3: executes the command
// Step 4: if execve fails, exits with error code.
int	execute_child(char *argv[], int fd[], char *env[], size_t child)
{
	char	**cmd_child;

	if (set_in_and_out(argv, fd, child) == 1)
		return (perror("Error redirecting input/output"), EXIT_FAILURE);
	if (child == 1)
		cmd_child = retrieve_cmds(argv[2], env);
	else
		cmd_child = retrieve_cmds(argv[3], env);
	if (!cmd_child)
		return (perror("Error retrieving command"), EXIT_FAILURE);
	execve(cmd_child[0], cmd_child, env);
	free_double(cmd_child);
	perror("Error with execve");
	if (errno == ENOENT || errno == 22)
		return (127);
	return (errno);
}

int	open_file(char *file, size_t child_i)
{
	int	fd;

	if (child_i == 1)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			return (perror("Error opening infile"), -1);
		return (fd);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (perror("Error opening outfile"), -1);
	return (fd);
}

// protect & close unused fd
int	set_in_and_out(char *argv[], int pipe[], size_t child_i)
{
	int	read_end;
	int	write_end;

	if (child_i == 1)
	{
		read_end = open_file(argv[1], child_i);
		write_end = pipe[1];
		close(pipe[0]);
	}
	else
	{
		read_end = pipe[0];
		write_end = open_file(argv[4], child_i);
		//close(pipe[1]);
	}
	if (read_end == -1 || write_end == -1)
		return (perror("error opening file"), 1);
	if (dup2(read_end, STDIN_FILENO) == -1)
	{
		if (child_i == 1)
			close(pipe[1]);
		else
			close(pipe[0]);
		return (perror("Error redirecting STDIN to infile"), 1);
	}
	close(read_end);
	if (dup2(write_end, STDOUT_FILENO) == -1)
	{
		close(pipe[0]);
		return (perror("Error redirecting pipe to STDOUT"), 1);
	}
	close(pipe[1]);
	return (0);
}
