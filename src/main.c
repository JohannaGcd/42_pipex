/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:50 by jguacide          #+#    #+#             */
/*   Updated: 2024/05/12 16:53:24 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

// TODO: when parsing how to check for wrong command --> execve will exit with a specific error code to interpret
// TODO: Reallocate error return values/codes for mistakes of the same type 


int main(int argc, char *argv[], char *env[])
{
	// Step 1: get the command and the binary path to execute it (also checks for wrong input)
	char *first_cmd_path;
	char **first_cmd;
	char *second_cmd_path;
	char **second_cmd;

	// TODO: is this enough protection ? if yes, add step2 comment here. 
	if (argc != 5)
		return (perror("wrong argument input"), 1);


	first_cmd = get_cmd(argv[2]);
	if (first_cmd == NULL)
		return (perror("Not a valid command"), 1); // TODO: do I need to return with exit failure here?
	first_cmd_path = get_cmd_path(env, first_cmd[0]);
	if (!first_cmd_path)
	{
		free_double(first_cmd);
		return (EXIT_FAILURE);
	}
	second_cmd = get_cmd(argv[3]);
	if (!second_cmd)
	{
		free_double(first_cmd);
		free(first_cmd_path);
		return (EXIT_FAILURE);
	}
	second_cmd_path = get_cmd_path(env, second_cmd[0]);
	if (!second_cmd_path)
	{
		free_double(first_cmd);
		free(first_cmd_path);
		free_double(second_cmd);
		return (EXIT_FAILURE);
	}
	// Step 2: create a pipe
	int fd[2];
	pipe(fd);
	if (pipe(fd) == -1)
		return (perror("Error creating pipe."), 2);

	// Step 3: Fork the first child process
	pid_t id1 = fork();
	if (id1 == -1)
		return (perror("Error forking child process."), 3);
	
	// Step 4: In the first child process, execute the first command
	if (id1 == 0)
	{
		// In First Child
		// Step 4.1: open the infile
		int infile = open(argv[1], O_RDONLY, 0777);
		if (infile == -1)
			return (perror("Error opening file"), 1);
		// Step 4.2: use dup2 to redirect reading from STDIN to the infile. To remember: "dup2(int oldfd, int newfd)" -> "I want newfd to point to oldfd" 
		if (dup2(infile, STDIN_FILENO) == -1)
			return (perror("Error redirecting STDIN to infile"), 1);
		// Step 4.3: likewise, redirect STDOUT to the write-end of the pipe (fd[1])
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror("Error redirecting pipe to STDOUT"), 1);
		// Step 4.4: close all unused fd.
		close(fd[0]);
		close(fd[1]);
		close(infile);
		// Step 4.5: use execve to perform the command.
		char *args[] = {first_cmd_path, first_cmd[1], NULL};
		if (execve(first_cmd[0], args, env) == -1)
		{
			perror("Error with execve"); 
			exit(EXIT_FAILURE);
		}
	}
	// Step 5: close the unused fd before forking the second child. Here, second child doesn't need fd[1].
	close(fd[1]);

	// Step 6: Fork the second child
	pid_t id2 = fork();
	if (id2 == -1)
		return (perror("Error forking second child process."), 2);
	if (id2 == 0)
	{
		// In Second Child
		// Step 6.1: open the outfile
		int outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
		if (outfile == -1)
			return (perror("Error opening outfile"), 3);
		// Step 6.2: redirect STDIN to the read-end of the pipe (fd[0])
		dup2(fd[0], STDIN_FILENO); 
		// Step 6.3: redirect STDOUT to outfile
		dup2(outfile, STDOUT_FILENO);
		// Step 6.4: close unused fd -> thanks to the redirection, execve will use STDOUT to output
		close(fd[0]);
		close(outfile);
	
		// Step 6.5: use execve to perform the second command.
		char *args[] = {second_cmd_path, second_cmd[1], NULL};
		if (execve(first_cmd[0], args, env) == -1)
		{
			perror("Error with execve"); 
			exit(EXIT_FAILURE);
		}
	}

	// In Parent
	// Step 7: Close all remaining file descriptors.
	close(fd[0]);
	// Step 8: Wait for children to execute
	int status1;
	int status2;
	int child2ExitStatus;
	pid_t f_child;
	pid_t s_child;

	f_child = waitpid(id1, &status1, 0);
	// retrieve the exit status of the last
	if (WIFEXITED(status1))
		ft_printf("Child process terminated normally with exit status : %d\n", WEXITSTATUS(status1));
	else 
		ft_printf("Child process terminated abnormally.\n");

	s_child = waitpid(id1, &status2, 0);
	if (WIFEXITED(status2))
	{
		child2ExitStatus = WEXITSTATUS(status2);
		ft_printf("Child process terminated normally with exit status : %d\n", child2ExitStatus);
		exit(child2ExitStatus);
	}
	else 
	{
		ft_printf("Child process terminated abnormally.\n");
		exit(EXIT_FAILURE);

	}
	return (0);
}
// TODO: strerror?
