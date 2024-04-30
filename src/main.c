/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguacide <jguacide@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:50 by jguacide          #+#    #+#             */
/*   Updated: 2024/04/30 16:06:35 by jguacide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
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
void get_env(char *env[], char *cmd)
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
	printf("%s", env[i]);
	// Skip PATH= and split the string 
	char *path = env[i] + 5;
	char **path_dir = ft_split(path, ':');
	// Test the command
	i = 0;
	while (path_dir[i] != NULL)
	{
		char *dir = path_dir[i];
		char *full_cmd = ft_strjoin(dir, "/");	
		full_cmd = ft_strjoin(full_cmd, cmd);
		ft_printf("%s\n", full_cmd);
		char *args[] = {full_cmd, cmd};
		execve(full_cmd, args, NULL);
		free(full_cmd);
		i++;
	}
	ft_free(path_dir);
	
}


int main(int argc, char *argv[], char *env[])
{
	// Parse the env array to find the PATH substring
	get_env(env, "ls");

	return (0);
}
