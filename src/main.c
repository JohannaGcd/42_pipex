/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:50 by jguacide          #+#    #+#             */
/*   Updated: 2024/05/06 16:33:34 by jguacide         ###   ########.fr       */
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
		char *step1_cmd = ft_strjoin(dir, "/");
		if (!step1_cmd)
		{
			printf("error with first strjoin.");
			ft_free(path_dir);
			return (NULL);
		}
		char *full_cmd = ft_strjoin(step1_cmd, cmd);
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
	first_cmd = get_cmd_path(env, argv[2]);
	if (first_cmd == NULL)
	{
		ft_printf("Not valid command");
		return (1);
	}
	// And second one
	second_cmd = get_cmd_path(env, argv[3]);
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
		// TODO:open file, use fd and redirect it 
		dup2(fd[1], STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		char *args[] = {first_cmd, NULL};
		execve(first_cmd, args, NULL);// 3rd argument is the environment list env
		// TODO: take care of case if exec fails (other code will keep executing)
		// TODO: I need to cater to the only two commands listed in the subject?
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
		// close unused fd: write end
		// dup read end to STDIN 
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		// read from STDIN 
		read(STDIN_FILENO, &, )
		// TODO: dup to whatever argv[4] was specified as 
		
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
