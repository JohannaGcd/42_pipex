/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:50 by jguacide          #+#    #+#             */
/*   Updated: 2024/05/07 12:15:25 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// when parsing check for wrong command
//
// Parse the env array to find the PATH substring
// parse the whole command inbeween quotes, it's not "ls -l" but "ls" "-l"
// TODO: separate this function so that one returns new_cmd and the other the full path (that one is done already)
char *get_cmd_path(char *env[], char *cmd)
{
	int i;
	char **new_cmd;
	
	i = 0;
	// get single command from argv ("ls -la" become double array with "ls" and "-la")
	new_cmd = ft_split(cmd, ' ');
	if (!new_cmd)
	{
		ft_free(new_cmd); // check this one, doesn't seem to free all date inside but just to free the double pointer
	}
	//TODO: protect split -> create function to free double 
	
	while (env[i] != NULL)
	{
		// loop through env[][], find PATH substring
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	// Skip PATH= and split the string 
	char *path = env[i] + 5;
	char **path_dir = ft_split(path, ':');
	//TODO: protect split
	
	//Testing the command to find the right path
	i = 0;
	while (path_dir[i] != NULL)
	{
		char *dir = path_dir[i];
		// adding "/" after the potential path
		char *step1_cmd = ft_strjoin(dir, "/");
		// protecting strjoin in case of failure
		if (!step1_cmd)
		{
			printf("error with first strjoin.");
			ft_free(path_dir);// see above, check ft_Free -> not sure it frees all the date inside
			return (NULL);
		}
		// adding the command (index 0) at te end of the path
		char *full_cmd = ft_strjoin(step1_cmd, new_cmd[0]);
		if (access(full_cmd, X_OK) == 0)
		{
			ft_free(path_dir);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	ft_free(path_dir);
	return (NULL);
}


int main(int argc, char *argv[], char *env[])
{
	// Parse the env array to find the PATH substring
	// TODO: How to deal with file1? input -> how do i link it with the command?
	char *first_cmd;
	char *second_cmd;
	// With first command
	first_cmd = get_cmd_path(env, argv[3]);
	if (first_cmd == NULL)
	{
		ft_printf("Not valid command");
		return (1);
	}
	// And second one
	second_cmd = get_cmd_path(env, argv[4]);
	if (second_cmd == NULL)
	{
		ft_printf("Not a valid command");
		return (1);
	}
	// Create pipe	
	int fd[2];
	pipe(fd);
	if (pipe(fd) == -1)
	{
		printf("An error occured with opening the pipe.\n");
		return (1);
	}
	// Fork first child
	int id1 = fork();
	if (id1 == -1)
	{
		printf("An error occured with first fork.\n");
		return (2);
	}
	if (id1 == 0)
	{
		// In CHILD 
		int fd_file = open(argv[1], O_WRONLY | O_CREAT, 0777);
		if (fd_file == -1)
			return (perror("Error opening file"), 1);
		if (dup2(STDIN_FILENO, fd_file) == -1)
			return (perror("Error redirecting STDIN to infile"), 1);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror("Error redirecting pipe to STDOUT"), 1);
		// close unused fd: read end
		close(fd_file); // necessary to close or not?
		close(fd[0]);
		close(fd[1]);
		char *args[] = {new_cmd[0], new_cmd[1], NULL}; // what if there is no new_cmd 1 ? TODO: populate args with a while loop?
		if (execve(first_cmd, args, env) == -1)
			return (perror("Error with execve"), 1);
		return (0);
	}

	// Fork second child
	int id2 = fork();
	if (id2 == -1)
	{
		printf("An error occured with second fork.\n");
		return (2);
	}
	if (id2 == 0)
	{
		// in CHILD
		int outfile = open(argv[4], O_RDONLY);
		dup2(fd[0], STDIN_FILENO);
		dup2(STDOUT_FILENO, outfile);
		close(fd[1]);
		close(fd[0]);
		// TODO: how to knpw what amount to read? use get_next_line?
		read(STDIN_FILENO, &, sizeof(?));
		write(outfile, &OUTPUTDEMACMD)
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
