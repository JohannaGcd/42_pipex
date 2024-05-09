/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:50 by jguacide          #+#    #+#             */
/*   Updated: 2024/05/09 11:37:15 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO: when parsing how to check for wrong command --> execve will exit with a specific error code to interpret
// TODO: Reallocate error return values/codes for mistakes of the same type 


int main(int argc, char *argv[], char *env[])
{
	// Step 1: get the command and the binary path to execute it (also checks for wrong input)
	char *first_cmd_path;
	char **first_cmd;
	char *second_cmd_path;
	char **second_cmd;

	first_cmd = get_cmd(argv[2]);
	first_cmd_path = get_cmd_path(env, first_cmd[0]);
	if (first_cmd == NULL)
		return (perror("Not a valid command"), 1);
	second_cmd = get_cmd_path(env, argv[3]);
	if (second_cmd == NULL)
		return (perror("Not a valid command"), 1);
	
	// Step 2: create a pipe
	int fd[2];
	pipe(fd);
	if (pipe(fd) == -1)
		return (perror("Error creating pipe."), 2);

	// Step 3: Fork the first child process
	int id1 = fork();
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
			return (perror("Error with execve"), 1);
		return (0);
	}
	// Step 5: close the unused fd before forking the second child. Here, second child doesn't need fd[1].
	close(fd[1]);

	// Step 6: Fork the second child
	int id2 = fork();
	if (id2 == -1)
	{
		printf("An error occured with second fork.\n");
		return (2);
	}
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
			return (perror("Error with execve"), 1);
		return (0);
	}

	// TODO: In parent wait for both children to execute and grab error code with waitpid
	// TODO: on success, execve does not retour, retunrs -1 for error and errno is set appropriately -> look into it to build the perror
	// TODO: build function to free all data inside a double pointer


	// In Parent
	// Step 7: Close all remaining file descriptors.
	close fd[0];
	// Step 8: Wait for children to execute
	int status1;
	waitpid(id1, &status1, 0); // TODO: what am I supposed to do in Parent? a macro 
	// retrieve the exit status of the last 
	if (WIFEXITED(status1) != 0)
	{
		// TODO: handle error in case execve fails
		printf("execve failed in first child.\n");
		return (3);
	}
	return (0);
	// have to wait on my two children
	// exit with exit cde of lats child\
	// strerror?
	// closing all unused fd from the start
	// close all of them then 
}
