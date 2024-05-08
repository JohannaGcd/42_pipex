/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:50 by jguacide          #+#    #+#             */
/*   Updated: 2024/05/08 13:49:04 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <unistd.h>

// when parsing check for wrong command
// Parse the env array to find the PATH substring
// parse the whole command inbeween quotes, it's not "ls -l" but "ls" "-l"
// TODO: separate this function so that one returns new_cmd and the other the full path (that one is done already)
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
		// Step 4.1: open the infile
		int infile = open(argv[1], O_RONLY | O_CREAT, 0777); // TODO: should i create it if no in file or send error?
		if (infile == -1)
			return (perror("Error opening file"), 1);
		// Step 4.2: use dup2 to redirect reading from STDIN to the infile. 
		if (dup2(infile, STDIN_FILENO) == -1)
			return (perror("Error redirecting STDIN to infile"), 1);
		// Step 4.3: likewise, redirect fd[1] to STDOUT 
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

	// Step 5: Fork the second child
	int id2 = fork();
	if (id2 == -1)
	{
		printf("An error occured with second fork.\n");
		return (2);
	}
	if (id2 == 0)
	{
		// Step 5.1: open the outfile
		int outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
		if (outfile == -1)
			return (perror("Error opening outfile"), 3);
		// Step2: redirect STDIN to pipe
		dup2(fd[0], STDIN_FILENO);
		// Step 5.3: redirect STDOUT to outfile
		dup2(outfile, STDOUT_FILENO);
		// Step 5.4: close unused fd
		close(fd[1]);
		close(fd[0]);
		close(outfile);
	
		// Step 5.5: use execve to perform the second command.
		char *args[] = {second_cmd_path, second_cmd[1], NULL};
		if (execve(first_cmd[0], args, env) == -1)
			return (perror("Error with execve"), 1);
		return (0);
	}

	// in parent wait for both children to execute and grab error code with waitpid
	// on success, execve does not retour, retunrs -1 for error and errno is set appropriately -> look into it to build the perror
	int status1;
	
	waitpid(id1, &status1, 0);
	// retrieve the exit status of the last 
	if (WIFEXITED(status1) != 0)
	{
		// TODO: handle error in case execve fails
		printf("execve failed in first child.\n");
		return (3);
	}
	return (0);
}
