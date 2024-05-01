/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:50 by jguacide          #+#    #+#             */
/*   Updated: 2024/05/01 13:55:12 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// METHOD:
// 1. Parse command line argument with env
// 2. create pipe
// 3. Fork child (and close unused fd)
// 4. execute first command in first child
// 5. fork another child
// 6. execute second command
// 7. Parent: close unused fd, wait for children
// 8. open / close input / output files
// 9. close all

// Parse the env array to find the PATH substring
char *get_cmd_path(char *env[], char *cmd)
{
	int i;

	i = 0;
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
	// Test the command
	i = 0;
	while (path_dir[i] != NULL)
	{
		char *dir = path_dir[i];
		char *step1_cmd = ft_strjoin(dir, "/");	// TODO: protect strjoin: free the whole double array in case of error
		char *full_cmd = ft_strjoin(step1_cmd, cmd);
		if (access(full_cmd, X_OK) == 0)
		{
			ft_free(path_dir);
			return (full_cmd);
		}// change args + check for return value if works or didnt work
		free(full_cmd);
		i++;
	}
	ft_free(path_dir);
// access if return value works, return that . if didnt owkr free evrything i've allocated!
	return (NULL);
}


int main(int argc, char *argv[], char *env[])
{
	// Parse the env array to find the PATH substring
	char *first_cmd;
	char *second_cmd;
	// With first command
	first_cmd = get_cmd_path(env, argv[1]);
	if (first_cmd == NULL)
	{
		ft_printf("Not valid command");
		return (1);
	}
	// And second one
	second_cmd = get_cmd_path(env, argv[2]);
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
		// close unused fd: read end
		close(fd[0]);
		char args[] = {first_cmd, NULL};
		execve(full_cmd, args, NULL);
		// TODO: How to retrieve output if execve deletes all the code? to the terminal?
		// DO I need to cater to the only two commands listed in the subject?
		
		
		




		close(fd[1]);
	}

	// Fork second child
	int id2 = fork();
	if (id2 == -1)
	{
		printf("An error occured with second fork.\n");
		return (2);
	}
	if (id == 0)
	{
		// in CHILD
		// close unused fd: write end
		close(fd[1]);
		// TODO: HOW TO RETRIEVE DATA FROM FIRST CHILD?
		read(fd[0], &)



		close(fd[0]);
		
	
		
	}
	// in parent wait for both children to execute and grab error code with waitpid
	int status1;
	
	waitpid(id1, &status, 0);
	if (WIFEXITED(status) != 0)
	{
		// TODO: handle error in case execve fails
		printf("execve failed in first child.\n")
		return (3);
	}
	return (0);
}
